/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/15 01:43:55 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//protect functions ??

void	cmd_exec(t_exp *exp, t_list *list, char **envp)
{
	if (list->option[0] && is_builtin(list->option))
	{
		handle_redirs(list, exp);
		exec_builtin(&exp, list->option);
		exit(0);
	}
	else
	{
		handle_redirs(list, exp);
		list->option[0] = get_cmd_path(exp, list->option[0]);
		if (list->option[0]
			&& execve(list->option[0], list->option, envp) == -1)
		{
			perror("execve");
			exp->status = 127;
			exit(127);
		}
	}
}

int	cmd_process(t_exp *exp, t_list *list, char **envp, t_exec *data)
{
	while (list)
	{
		data->pid[data->i] = fork();
		if (data->pid[data->i] < 0)
			perror("fork");
		else if (data->pid[data->i] == 0)
		{
			setup_signals(1);
			child_io(data, list);
			cmd_exec(exp, list, envp);
		}
		else
			parent_io(data, list);
		list = list->next;
		data->i++;
	}
	return (0);
}

void	children_wait(t_exec *data, t_exp *exp, struct termios *term)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		waitpid(data->pid[i], &data->status, 0);
		i++;
	}
	if (WIFSIGNALED(data->status))
	{
		tcsetattr(STDIN_FILENO, TCSANOW, term); // 9ra 3la hadchi
		if (WTERMSIG(data->status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		else if (WTERMSIG(data->status) == SIGINT)
			write(1, "\n", 1);
		exp->status = WTERMSIG(data->status) + 128;
	}
	else if (WIFEXITED(data->status))
		exp->status = WEXITSTATUS(data->status);
}

int	exec(t_exp *exp, t_list *list, char **envp, struct termios *term)
{
	t_exec	data;

	data = (t_exec){0}; // concept of initialization vs assignement
	if (!list || !list->option)
		return (exp->status = 1, 1);
	data.std_in = dup(0);
	data.std_out = dup(1);
	data.pid = NULL;
	data.i = 0;
	setup_signals(0);
	data.count = ft_lstsize(list);
	if (data.count == 1 && is_builtin(list->option))
		return (onecmd_builtin(exp, list));
	data.pid = malloc(sizeof(int) * data.count);
	if (!data.pid)
		return (exp->status = 1, 1);
	cmd_process(exp, list, envp, &data);
	children_wait(&data, exp, term);
	free(data.pid);
	dup2(data.std_in, 0);
	close(data.std_in);
	dup2(data.std_out, 1);
	close(data.std_out);
	return (0);
}

int	execute(t_list *list, t_exp *exp, char **envp)
{
	char			*tmp;
	struct termios	term;

	tcgetattr(0, &term);
	if (g_sig == 1)
	{
		g_sig = 0;
		return (0);
	}
	tmp = find_path(exp);
	if (!tmp)
		return (exp->status = 1, 1);
	if (exp)
		exp->path = ft_split(tmp, ':');
	if (!exp || !exp->path)
		return (exp->status = 1, 1);
	// free(tmp);
	exec(exp, list, envp, &term);
	return (0);
}

// int	exec(t_exp *exp, t_list *list, char **envp, struct termios *term)
// {
// 	int			fdpipe[2];
// 	int			std_in;
// 	int			std_out;
// 	int			*pid;
// 	int			i;
// 	int			count;
// 	static int	status;

// 	if (!list || !list->option)
// 		return (exp->status = 1, 1);
// 	std_in = dup(0);
// 	std_out = dup(1);
// 	pid = NULL;
// 	i = 0;
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);

// 	// signal(SIGQUIT, signal_handler2);
// 	count = ft_lstsize(list);
// 	if (count == 1 && is_builtin(list->option))
// 		onecmd_builtin(exp, list);
// 	else
// 	{
// 		pid = malloc(sizeof(int) * count);
// 		if (!pid)
// 			return (exp->status = 1, 1);
// 		while (list)
// 		{
// 			if (list->next && pipe(fdpipe) == -1)
// 			{
// 				perror("pipe");
// 				exit(1);
// 			}
// 			pid[i] = fork();
// 			if (pid[i] < 0)
// 				perror("fork");
// 			else if (pid[i] == 0)
// 			{
// 				signal(SIGINT, SIG_DFL);
// 				signal(SIGQUIT, SIG_DFL);
// 				if (i > 0)
// 				{
// 					dup2(std_in, 0);
// 					close(std_in);
// 				}
// 				if (list->next)
// 				{
// 					close(fdpipe[0]);
// 					dup2(fdpipe[1], 1);
// 					close(fdpipe[1]);
// 				}
// 				else
// 				{
// 					dup2(std_out, 1);
// 					close(std_out);
// 				}
// 				if (list->option[0] && is_builtin(list->option))
// 				{
// 					handle_redirs(list, exp);
// 					exec_builtin(&exp, list->option);
// 					dup2(fdpipe[0], 0);
// 					close(fdpipe[0]);
// 					dup2(fdpipe[1], 1);
// 					close(fdpipe[1]);
// 					exit(0);
// 				}
// 				else
// 					handle_redirs(list, exp);
// 				list->option[0] = get_cmd_path(exp, list->option[0]);
// 				if (list->option[0]
// 					&& execve(list->option[0], list->option, envp) == -1)
// 				{
// 					perror("execve");
// 					exp->status = 127;
// 					exit(127);
// 				}
// 			}
// 			else
// 			{
// 				if (i > 0)
// 					close(std_in);
// 				if (list->next)
// 				{
// 					close(fdpipe[1]);
// 					std_in = fdpipe[0];
// 				}
// 			}
// 			list = list->next;
// 			i++;
// 		}
// 		i = 0;
// 		while (i < count)
// 		{
// 			waitpid(pid[i], &status, 0);
// 			i++;
// 		}
// 		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
// 		{
// 			tcsetattr(STDIN_FILENO, TCSANOW, term);
// 			write(1, "Quit: 3\n", 8);
// 		}
// 		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 		{
// 			tcsetattr(STDIN_FILENO, TCSANOW, term);
// 			write(1, "\n", 1);
// 		}
// 		if (WIFEXITED(status))
// 			exp->status = (WEXITSTATUS(status));
// 		else if (WIFSIGNALED(status))
// 			exp->status = WTERMSIG(status) + 128;
// 		free(pid);
// 		dup2(std_in, 0);
// 		close(std_in);
// 		dup2(std_out, 1);
// 		close(std_out);
// 	}
// 	return (0);
// }
