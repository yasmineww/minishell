/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/15 23:19:41 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_redir(char **option, int i)
{
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
	if (!list->option)
		return (exp->status = 1, 1);
	while (list->option[i])
	{
		if (!ft_strncmp(list->option[i], "<<", 2))
		{
			dup2(list->infile, 0);
			close(list->infile);
			remove_redir(list->option, i);
			continue ;
		}
		else if (list->option[i] && !ft_strncmp(list->option[i], ">>", 2))
			return (handle_append(list, i, exp), exp->status = 1, 1);
		else if (list->option[i] && !ft_strncmp(list->option[i], ">", 1))
			return (handle_redir_out(list, i, exp), exp->status = 1, 1);
		else if (list->option[i] && !ft_strncmp(list->option[i], "<", 1))
			return (handle_redir_in(list, i, exp), exp->status = 1, 1);
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
		if (exp->ambiguous)
			return (ft_error("bash: ", list->option[i + 1],
					"ambiguous redirect"), exp->ambiguous = 0, exp->status = 1, 1);
		list->infile = open(list->option[i + 1], O_RDONLY);
		if (list->infile == -1)
			return (perror("open"), exp->status = 1, 1);
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
		if (exp->ambiguous)
			return (ft_error("bash: ", list->option[i + 1],
					"ambiguous redirect"), exp->ambiguous = 0, exp->status = 1, 1);
		list->outfile = open(list->option[i + 1], O_RDWR
				| O_CREAT | O_TRUNC, 0644);
		if (list->outfile == -1)
			return (perror("open"), exp->status = 1, 1);
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
		if (exp->ambiguous)
			return (ft_error("bash: ", list->option[i + 1],
					"ambiguous redirect"), exp->ambiguous = 0, exp->status = 1, 1);
		list->outfile = open(list->option[i + 1], O_RDWR
				| O_CREAT | O_APPEND, 0644);
		if (list->outfile == -1)
			return (perror("open"), exp->status = 1, 1);
		dup2(list->outfile, 1);
		close(list->outfile);
		remove_redir(list->option, i);
	}
	return (0);
}
