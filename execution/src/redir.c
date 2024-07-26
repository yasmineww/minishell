/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/26 00:52:06 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_redir(char **option, int i)
{
	if (ft_2dlen(option) < 3)
	{
		free(option[i]);
		option[i] = NULL;
		if (option[i + 1])
		{
			free(option[i + 1]);
			option[i + 1] = NULL;
		}
		return ;
	}
	free(option[i]);
	free(option[i + 1]);
	while (option[i + 2])
	{
		option[i] = option[i + 2];
		i++;
	}
	option[i] = NULL;
	if (option[i + 1])
		option[i + 1] = NULL;
}

int	handle_redirs(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->list->option[i])
	{
		if (!ft_strncmp(mini->list->option[i], "<<", 2))
		{
			dup2(mini->list->infile, 0);
			remove_redir(mini->list->option, i);
			continue ;
		}
		else if (mini->list->option[i] && !ft_strncmp(mini->list->option[i], ">>", 2))
		{
			if (mini->list->flags.ambiguous || mini->list->flags.special)
			{
				ft_error("Minishell:", mini->list->option[i + 1], "ambiguous redirect\n");
				mini->list->flags.ambiguous = 0;
				mini->status = 1;
				return (1);
			}
			if (handle_append(mini, i))
				return (1);
		}
		else if (mini->list->option[i] && !ft_strncmp(mini->list->option[i], ">", 1))
		{
			if (mini->list->flags.ambiguous || mini->list->flags.special)
			{
				ft_error("Minishell:", mini->list->option[i + 1], "ambiguous redirect\n");
				mini->list->flags.ambiguous = 0;
				mini->status = 1;
				return (1);
			}
			if (handle_redir_out(mini, i))
				return (1);
		}
		else if (mini->list->option[i] && !ft_strncmp(mini->list->option[i], "<", 1))
		{
			if (mini->list->flags.ambiguous || mini->list->flags.special)
			{
				ft_error("Minishell:", mini->list->option[i + 1], "ambiguous redirect\n");
				mini->list->flags.ambiguous = 0;
				mini->status = 1;
				return (1);
			}
			if (handle_redir_in(mini, i))
				return (1);
		}
		else
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
			ft_error("Minishell:", mini->list->option[i + 1], "No such file or directory\n");
			return ((mini->status = 1), 1);
		}
		dup2(mini->list->infile, 0);
		close(mini->list->infile);
		remove_redir(mini->list->option, i);
	}
	return (0);
}

int	handle_redir_out(t_mini *mini, int i)
{
	mini->list->outfile = -1;
	if (mini->list->option[i + 1])
	{
		mini->list->outfile = open(mini->list->option[i + 1], O_RDWR
				| O_CREAT | O_TRUNC, 0644);
		if (mini->list->outfile == -1)
		{
			ft_error("Minishell:", mini->list->option[i + 1], "No such file or directory\n");
			return (mini->status = 1, 1);
		}
		dup2(mini->list->outfile, 1);
		close(mini->list->outfile);
		remove_redir(mini->list->option, i);
	}
	return (0);
}

int	handle_append(t_mini *mini, int i)
{
	mini->list->outfile = -1;
	if (mini->list->option[i + 1])
	{
		mini->list->outfile = open(mini->list->option[i + 1], O_RDWR
				| O_CREAT | O_APPEND, 0644);
		if (mini->list->outfile == -1)
		{
			ft_error("Minishell:", mini->list->option[i + 1], "No such file or directory\n");
			return (mini->status = 1, 1);
		}
		dup2(mini->list->outfile, 1);
		close(mini->list->outfile);
		remove_redir(mini->list->option, i);
	}
	return (0);
}
