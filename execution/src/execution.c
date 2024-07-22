/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/22 23:14:50 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//protect functions ??
// ambiguous builtin

void	cmd_exec(t_exp *exp, t_list *list, char **envp, t_exec *data)
{
	if (list->option[0] && is_builtin(list->option))
	{
		if (handle_redirs(list, exp))
			exit(1);
		exec_builtin(&exp, list->option, list);
		dup2(data->fdpipe[0], 0);
		close(data->fdpipe[0]);
		dup2(data->fdpipe[1], 1);
		close(data->fdpipe[1]);
		exit(0);
	}
	else if (list->option[0])
	{
		if (handle_redirs(list, exp))
			exit(1);
		if (!list->option[0])
			exit(0);
		// if (exp->test)
		// {
		// 	//free the old one 2d array ig
		// 	list->option = ft_split_spaces(list->option[0]);
		// }
		list->option[0] = get_cmd_path(exp, list->option[0]);
		if (list->option[0] && execve(list->option[0], list->option, envp))
		{
			printf("option[0] = %s\n", list->option[0]);
			if (list->option[0][0] && list->option[0][0] == '/')
			{
				opendir(list->option[0]);
				ft_error("Minishell:", list->option[0], ": is a directory\n");
				exp->status = 126;
				exit(126);
			}
			ft_error("Minishell:", list->option[0], ": command not found\n");
			exp->status = 127;
			exit(127);
		}
	}
}

int	cmd_process(t_exp *exp, t_list *list, char **envp, t_exec *data)
{
	while (list)
	{
		if (list->next && pipe(data->fdpipe) == -1)
			return (perror("pipe"), exp->status = 1, 1);
		data->pid[data->i] = fork();
		if (data->pid[data->i] < 0)
			return (perror("fork"), exp->status = 1, 1);
		else if (data->pid[data->i] == 0)
		{
			setup_signals(1);
			child_io(data, list);
			cmd_exec(exp, list, envp, data);
			// exit(0);
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

int	exec(t_exp **exp, t_list *list, char **envp, struct termios *term)
{
	t_exec	data;

	data = (t_exec){0}; // concept of initialization vs assignement
	if (!list || !list->option)
		return ((*exp)->status = 1, 1);
	int dups = dup(0);
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
		return ((*exp)->status = 1, 1);
	printf("count = %d\n", data.count);
	int i = 0;
	while (list)
	{
		while (list->option[i])
		{
			fprintf(stderr, "option[%d] = %s\n", i, list->option[i]);
			i++;
		}
		list = list->next;
	}
	if (cmd_process(*exp, list, envp, &data))
		return ((*exp)->status = 1, 1);
	children_wait(&data, *exp, term);
	free(data.pid);
	dup2(dups, 0);
	close(dups);
	close(data.std_in);
	close(data.std_out);
	return (0);
}

int	execute(t_list *list, t_exp **exp, char **envp)
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
	if (*exp && tmp)
	{
		if ((*exp)->path)
			ft_free((*exp)->path);
		(*exp)->path = ft_split(tmp, ':');
	}
	if (!(*exp) || !(*exp)->path)
		return ((*exp)->status = 1, 1);
	// free(tmp);
	exec(exp, list, envp, &term);
	if (list->infile)
		close(list->infile);
	return (0);
}
