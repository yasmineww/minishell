/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/28 04:42:48 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirs_handler(t_mini *mini, int i, char *s, int (*handler)
	(t_mini *, int))
{
	if (mini->list->option[i] && !ft_strncmp
		(mini->list->option[i], s,
			ft_strlen(s)))
	{
		if (check_amb(mini, i))
			return (1);
		if (handler(mini, i))
			return (1);
		return (2);
	}
	return (0);
}

int	handle_redirs(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->list->option[i])
	{
		if (!ft_strncmp(mini->list->option[i], "<<", 2))
		{
			ft_dup2(mini->list->infile, 0);
			remove_redir(mini->list->option, i);
			continue ;
		}
		if (process_redir(mini, &i, ">>", handle_append))
			return (1);
		if (process_redir(mini, &i, ">", handle_redir_out))
			return (1);
		if (process_redir(mini, &i, "<", handle_redir_in))
			return (1);
		i++;
	}
	return (0);
}

int	handle_redir_in(t_mini *mini, int i)
{
	mini->list->infile = -1;
	if (mini->list->option[i + 1])
	{
		mini->list->infile = open(mini->list->option[i + 1], O_RDONLY);
		if (mini->list->infile == -1)
		{
			ft_error("Minishell:", mini->list->option[i + 1],
				"No such file or directory\n");
			return ((mini->status = 1), 1);
		}
		ft_dup2(mini->list->infile, 0);
		close(mini->list->infile);
	}
	return (0);
}

int	handle_redir_out(t_mini *mini, int i)
{
	mini->list->outfile = -1;
	if (mini->list->option[i + 1])
	{
		mini->list->outfile = open(mini->list->option[i + 1], O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (mini->list->outfile == -1)
		{
			ft_error("Minishell:", mini->list->option[i + 1],
				"No such file or directory\n");
			return (mini->status = 1, 1);
		}
		ft_dup2(mini->list->outfile, 1);
		close(mini->list->outfile);
	}
	return (0);
}

int	handle_append(t_mini *mini, int i)
{
	mini->list->outfile = -1;
	if (mini->list->option[i + 1])
	{
		mini->list->outfile = open(mini->list->option[i + 1], O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (mini->list->outfile == -1)
		{
			ft_error("Minishell:", mini->list->option[i + 1],
				"No such file or directory\n");
			return (mini->status = 1, 1);
		}
		ft_dup2(mini->list->outfile, 1);
		close(mini->list->outfile);
	}
	return (0);
}
