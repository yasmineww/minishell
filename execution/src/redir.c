/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/11 18:36:53 by mbenchel         ###   ########.fr       */
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

void	handle_redirs(t_list *list, t_exp *exp)
{
	int	i;

	i = 0;
	if (!list->option)
		return ;
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
			handle_append(list, i, exp);
		else if (list->option[i] && !ft_strncmp(list->option[i], ">", 1))
			handle_redir_out(list, i, exp);
		else if (list->option[i] && !ft_strncmp(list->option[i], "<", 1))
			handle_redir_in(list, i, exp);
		else
			i++;
	}
}

int	handle_redir_in(t_list *list, int i, t_exp *exp)
{
	list->infile = -1;
	if (list->option[i + 1])
	{
		if (exp->ambiguous)
			return (ft_error("bash: ", list->option[i + 1],
					"ambiguous redirect"), exit(1), 1);
		list->infile = open(list->option[i + 1], O_RDONLY);
		if (list->infile == -1)
		{
			perror("open");
			exit(1);
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
		if (exp->ambiguous)
			return (ft_error("bash: ", list->option[i + 1],
					"ambiguous redirect"), exit(1), 1);
		list->outfile = open(list->option[i + 1], O_RDWR
				| O_CREAT | O_TRUNC, 0644);
		if (list->outfile == -1)
		{
			perror("open");
			exit(1);
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
		if (exp->ambiguous)
			return (ft_error("bash: ", list->option[i + 1],
					"ambiguous redirect"), exit(1), 1);
		list->outfile = open(list->option[i + 1], O_RDWR
				| O_CREAT | O_APPEND, 0644);
		if (list->outfile == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(list->outfile, 1);
		close(list->outfile);
		remove_redir(list->option, i);
	}
	return (0);
}
