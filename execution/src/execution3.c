/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:55:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/28 20:05:04 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_execve(t_mini *mini)
{
	struct stat	path_stat;

	if (stat(mini->list->option[0], &path_stat) == 0
		&& S_ISDIR(path_stat.st_mode))
	{
		ft_error("Minishell:", mini->list->option[0],
			"is a directory\n");
		mini->status = 126;
		exit(126);
	}
	else
	{
		ft_error("Minishell:", mini->list->option[0],
			"command not found\n");
		mini->status = 127;
		exit(127);
	}
}

int	builtin_pipe(t_exec *data, t_mini *mini)
{
	if (mini->list->option[0] && is_builtin(mini->list->option))
	{
		if (handle_redirs(mini))
			exit(1);
		exec_builtin(mini, mini->list->option);
		ft_dup2(data->fdpipe[0], 0);
		close(data->fdpipe[0]);
		ft_dup2(data->fdpipe[1], 1);
		close(data->fdpipe[1]);
		free_list(mini->list);
		return (0);
	}
	return (1);
}
