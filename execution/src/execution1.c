/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:29:54 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/28 06:48:34 by mbenchel         ###   ########.fr       */
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

char	*get_cmd_path(char *cmd, t_mini *mini)
{
	char	*cmdpath;
	char	*prefix;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	i = 0;
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	while (mini->path && mini->path[i])
	{
		prefix = ft_strjoin(mini->path[i], "/");
		cmdpath = ft_strjoin(prefix, cmd);
		free(prefix);
		if (!access(cmdpath, X_OK))
			return (cmdpath);
		free(cmdpath);
		i++;
	}
	return (mini->status = 127,
		ft_error("Minishell:", cmd, "command not found\n"),
		exit(127), NULL);
}

void	child_io(t_exec *data, t_list *list)
{
	if (data->i > 0)
	{
		ft_dup2(data->std_in, 0);
		close(data->std_in);
	}
	if (list->next)
	{
		close(data->fdpipe[0]);
		ft_dup2(data->fdpipe[1], 1);
		close(data->fdpipe[1]);
	}
	else
	{
		ft_dup2(data->std_out, 1);
		close(data->std_out);
	}
}
