/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/26 00:07:50 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//protect functions ??
// ambiguous builtin

void	cmd_exec(char **envp, t_exec *data, t_mini *mini)
{
	if (mini->list->option[0] && is_builtin(mini->list->option))
	{
		if (handle_redirs(mini))
			exit(1);
		exec_builtin(mini, mini->list->option);
		dup2(data->fdpipe[0], 0);
		close(data->fdpipe[0]);
		dup2(data->fdpipe[1], 1);
		close(data->fdpipe[1]);
		free_list(mini->list);
		exit(0);
	}
	else
	{
		if (handle_redirs(mini))
			exit(1);
		if (!mini->list->option[0])
			exit(0);
		if (mini->exp->test) //mini->list->flags.special
		{
			//free the old one 2d array ig
			mini->list->option = ft_split_spaces(mini->list->option[0]);
		}
		mini->list->option[0] = get_cmd_path(mini->exp, mini->list->option[0] , mini);
		if (mini->list->option[0] && execve(mini->list->option[0], mini->list->option, envp))
		{
			if (mini->list->option[0][0] && mini->list->option[0][0] == '/')
			{
				opendir(mini->list->option[0]);
				ft_error("Minishell:", mini->list->option[0], "is a directory\n");
				mini->status = 126;
				exit(126);
			}
			ft_error("Minishell:", mini->list->option[0], "command not found\n");
			mini->status = 127;
			exit(127);
		}
	}
}

int	cmd_process(char **envp, t_exec *data, t_mini *mini)
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
			cmd_exec(envp, data, mini);
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
		tcsetattr(STDIN_FILENO, TCSANOW, term); // 9ra 3la hadchi
		if (WTERMSIG(data->status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		else if (WTERMSIG(data->status) == SIGINT)
			write(1, "\n", 1);
		mini->status = WTERMSIG(data->status) + 128;
	}
	else if (WIFEXITED(data->status))
		mini->status = WEXITSTATUS(data->status);
}

int	exec(t_mini *mini, char **envp, struct termios *term)
{
	t_exec	data;

	data = (t_exec){0}; // concept of initialization vs assignement
	if (!mini->list || !mini->list->option)
		return (mini->status = 1, 1);
	int dups = dup(0);
	data.std_in = dup(0);
	data.std_out = dup(1);
	data.pid = NULL;
	data.i = 0;
	setup_signals(0);
	data.count = ft_lstsize(mini->list);
	if (data.count == 1 && is_builtin(mini->list->option))
		return (onecmd_builtin(mini));
	data.pid = malloc(sizeof(int) * data.count);
	if (!data.pid)
		return (mini->status = 1, 1);
	if (cmd_process(envp, &data, mini))
		return (mini->status = 1, 1);
	children_wait(&data, term, mini);
	free(data.pid);
	dup2(dups, 0);
	close(dups);
	close(data.std_in);
	close(data.std_out);
	return (0);
}

void	update_underscore(t_exp **exp, char *last_arg)
{
	t_exp	*tmp;
	t_exp	*new;

	tmp = *exp;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, "_"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(last_arg);
			return ;
		}
		tmp = tmp->next;
	}
	new = create_node("_", last_arg);
	if (new)
		ft_lstadd_back(exp, new);
}

char *get_last_arg(char **option)
{
	int	i;

	i = 0;
	while (option[i + 1])
		i++;
	return (option[i]);
}

int	execute(t_mini *mini, char **envp)
{
	char			*tmp;
	struct termios	term;
	char			*last_arg;

	tcgetattr(0, &term);
	if (g_sig == 1)
		return (g_sig = 0 ,0);
	tmp = find_path(&mini->exp);
	if (mini->exp && tmp)
	{
		if (mini->exp->path)
			ft_free(mini->exp->path);
		mini->exp->path = ft_split(tmp, ':');
	}
	if (!mini->exp || !mini->exp->path)
		return (mini->status = 1, 1);
	last_arg = get_last_arg(mini->list->option);
	if (last_arg)
		update_underscore(&mini->exp, last_arg);
	exec(mini, envp, &term);
	if (mini->list && mini->list->infile)
		close(mini->list->infile);
	return (0);
}
