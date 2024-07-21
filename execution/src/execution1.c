/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:29:54 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/21 23:34:24 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parent_io(t_exec *data, t_list *list)
{
	if (data->i > 0)
		close(data->std_in);
	if (list->next)
	{
		close(data->std_in);
		close(data->fdpipe[1]);
		data->std_in = data->fdpipe[0];
	}
}

char	*get_cmd_path(t_exp *exp, char *cmd)
{
	char	*cmdpath;
	char	*prefix;
	int		i;

	if (!cmd)
		return (NULL);
	i = 0;
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	while (exp->path[i])
	{
		prefix = ft_strjoin(exp->path[i], "/");
		cmdpath = ft_strjoin(prefix, cmd);
		free(prefix);
		if (!access(cmdpath, X_OK))
			return (cmdpath);
		free(cmdpath);
		i++;
	}
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	return (exp->status = 127,
		ft_error("Minishell:", cmd, ": command not found\n"),
		exit(127), NULL);
}

void	setup_signals(int i)
{
	if (i == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	onecmd_builtin(t_exp **exp, t_list *list)
{
	int	std_in;
	int	std_out;
	int	i;

	i = 0;
	std_in = dup(0);
	std_out = dup(1);
	if (!list || !list->option || list->next)
		return ((*exp)->status = 1, 1);
	if (handle_redirs(list, *exp))
		return (1);
	exec_builtin(exp, list->option, list);
	while (list->option[i])
	{
		free(list->option[i]);
		list->option[i] = NULL;
		i++;
	}
	close(std_in);
	close(std_out);
	return (0);
}

void	child_io(t_exec *data, t_list *list)
{
	if (data->i > 0)
	{
		dup2(data->std_in, 0);
		close(data->std_in);
	}
	if (list->next)
	{
		close(data->fdpipe[0]);
		dup2(data->fdpipe[1], 1);
		close(data->fdpipe[1]);
	}
	else
	{
		dup2(data->std_out, 1);
		close(data->std_out);
	}
}
