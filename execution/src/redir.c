/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/23 14:25:18 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_redir(char **option, int i)
{
	if (ft_2dlen(option) < 3)
	{
		option[i] = NULL;
		if (option[i + 1])
			option[i + 1] = NULL;
		return ;
	}
	while (option[i] && option[i + 2])
	{
		option[i] = option[i + 2];
		i++;
	}
	option[i] = NULL;
	if (option[i + 1])
		option[i + 1] = NULL;
}

int	handle_redirs(t_list *list, t_exp *exp)
{
	int	i;

	i = 0;
	while (list->option[i])
	{
		if (!ft_strncmp(list->option[i], "<<", 2))
		{
			dup2(list->infile, 0);
			remove_redir(list->option, i);
			continue ;
		}
		else if (list->option[i] && !ft_strncmp(list->option[i], ">>", 2))
		{
			if (exp->ambiguous || exp->test)
			{
				ft_error("Minishell:", list->option[i + 1], "ambiguous redirect\n");
				exp->ambiguous = 0;
				exp->status = 1;
				return (1);
			}
			if (handle_append(list, i, exp))
				return (1);
		}
		else if (list->option[i] && !ft_strncmp(list->option[i], ">", 1))
		{
			if (exp->ambiguous || exp->test)
			{
				ft_error("Minishell:", list->option[i + 1], "ambiguous redirect\n");
				exp->ambiguous = 0;
				exp->status = 1;
				return (1);
			}
			if (handle_redir_out(list, i, exp))
				return (1);
		}
		else if (list->option[i] && !ft_strncmp(list->option[i], "<", 1))
		{
			if (exp->ambiguous || exp->test)
			{
				ft_error("Minishell:", list->option[i + 1], "ambiguous redirect\n");
				exp->ambiguous = 0;
				exp->status = 1;
				return (1);
			}
			if (handle_redir_in(list, i, exp))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	handle_redir_in(t_list *list, int i, t_exp *exp)
{
	list->infile = -1;
	if (list->option[i + 1])
	{
		list->infile = open(list->option[i + 1], O_RDONLY);
		if (list->infile == -1)
		{
			ft_error("Minishell:", list->option[i + 1], "No such file or directory\n");
			return ((exp->status = 1), 1);
		}
		dup2(list->infile, 0);
		close(list->infile);
		remove_redir(list->option, i);
	}
	return (0);
}

int	handle_redir_out(t_list *list, int i, t_exp *exp)
{
	list->outfile = -1;
	if (list->option[i + 1])
	{
		list->outfile = open(list->option[i + 1], O_RDWR
				| O_CREAT | O_TRUNC, 0644);
		if (list->outfile == -1)
		{
			ft_error("Minishell:", list->option[i + 1], "No such file or directory\n");
			return ((exp->status = 1), 1);
		}
		dup2(list->outfile, 1);
		close(list->outfile);
		remove_redir(list->option, i);
	}
	return (0);
}

int	handle_append(t_list *list, int i, t_exp *exp)
{
	list->outfile = -1;
	if (list->option[i + 1])
	{
		list->outfile = open(list->option[i + 1], O_RDWR
				| O_CREAT | O_APPEND, 0644);
		if (list->outfile == -1)
		{
			ft_error("Minishell:", list->option[i + 1], "No such file or directory\n");
			return ((exp->status = 1), 1);
		}
		dup2(list->outfile, 1);
		close(list->outfile);
		remove_redir(list->option, i);
	}
	return (0);
}
