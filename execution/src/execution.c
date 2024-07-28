/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/28 20:03:39 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_exec(t_exec *data, t_mini *mini)
{
	char		**envpp;

	if (!builtin_pipe(data, mini))
		exit(0);
	if (handle_redirs(mini))
		exit(1);
	if (!mini->list->option[0])
		exit(0);
	check_special(mini);
	mini->list->option[0] = get_cmd_path(mini->list->option[0], mini);
	envpp = turn_exp_array(mini);
	if (execve(mini->list->option[0], mini->list->option, envpp))
		check_execve(mini);
}

int	cmd_process(t_exec *data, t_mini *mini)
{
	t_list	*temp;

	temp = mini->list;
	while (mini->list)
	{
		if (mini->list->next && pipe(data->fdpipe) == -1)
			return (perror("pipe"), mini->status = 1, 1);
		data->pid[data->i] = fork();
		if (data->pid[data->i] < 0)
			return (perror("fork"), mini->status = 1, 1);
		else if (data->pid[data->i] == 0)
		{
			setup_signals(1);
			child_io(data, mini->list);
			cmd_exec(data, mini);
		}
		else
			parent_io(data, mini->list);
		mini->list = mini->list->next;
		data->i++;
	}
	free_list(temp);
	return (0);
}

void	children_wait(t_exec *data, struct termios *term, t_mini *mini)
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
		tcsetattr(STDIN_FILENO, TCSANOW, term);
		if (WTERMSIG(data->status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		else if (WTERMSIG(data->status) == SIGINT)
			write(1, "\n", 1);
		mini->status = WTERMSIG(data->status) + 128;
	}
	else if (WIFEXITED(data->status))
		mini->status = WEXITSTATUS(data->status);
}

int	exec(t_mini *mini, struct termios *term)
{
	t_exec	data;

	data = (t_exec){0};
	if (!mini->list || !mini->list->option)
		return (mini->status = 1, 1);
	data.dups = ft_dup(0);
	data.std_in = ft_dup(0);
	data.std_out = ft_dup(1);
	data.pid = NULL;
	data.i = 0;
	setup_signals(0);
	data.count = ft_lstsize(mini->list);
	if (data.count == 1 && is_builtin(mini->list->option))
		return (ft_close(data), onecmd_builtin(mini));
	data.pid = malloc(sizeof(int) * data.count);
	if (!data.pid)
		return (mini->status = 1, 1);
	if (cmd_process(&data, mini))
		return (free(data.pid), mini->status = 1, 1);
	children_wait(&data, term, mini);
	free(data.pid);
	ft_close(data);
	return (0);
}

int	execute(t_mini *mini)
{
	char			*tmp;
	struct termios	term;
	char			*last_arg;

	tcgetattr(0, &term);
	if (g_sig == 1)
		return (g_sig = 0, 0);
	if (mini->path_unset == 0)
	{
		tmp = find_path(&mini->exp);
		if (mini->exp && tmp)
		{
			if (mini->path)
				ft_free(mini->path);
			mini->path = ft_split(tmp, ':');
		}
	}
	last_arg = get_last_arg(mini->list->option);
	update_underscore(&mini->exp, last_arg);
	exec(mini, &term);
	if (mini->list && mini->list->infile)
		close(mini->list->infile);
	return (0);
}
