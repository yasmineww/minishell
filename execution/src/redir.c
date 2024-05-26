/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/26 23:18:28 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_redir_in(t_list *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	list->infile = -1;
	while (list->option[i])
	{
		if (!ft_strncmp(list->option[i], "<", 1))
		{
			if (list->option[i + 1])
			{
				list->infile = open(list->option[i + 1], O_RDONLY);
				if (list->infile == -1)
				{
					perror("open");
					break ;
				}
				dup2(list->infile, 0);
				close(list->infile);
				j = i;
				while (list->option[j])
				{
					list->option[j] = list->option[j + 2];
					j++;
				}
				continue ;
			}
		}
			i++;
	}
	return (0);
}
int	handle_redir_out(t_list *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	list->outfile = -1;
	while (list->option[i])
	{
		if (!ft_strncmp(list->option[i], ">", 1))
		{
			if (list->option[i + 1])
			{
				list->outfile = open(list->option[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
				if (list->outfile == -1)
				{
					perror("open");
					break ;
				}
				dup2(list->outfile, 1);
				close(list->outfile);
				j = i;
				while (list->option[j])
				{
					list->option[j] = list->option[j + 2];
					j++;
				}
				continue ;
			}
		}
			i++;
	}
	return (0);
}

int	handle_append(t_list *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	list->outfile = -1;
	while (list->option[i])
	{
		if (!ft_strncmp(list->option[i], ">>", 2))
		{
			if (list->option[i + 1])
			{
				list->outfile = open(list->option[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
				if (list->outfile == -1)
				{
					perror("open");
					break ;
				}
				dup2(list->outfile, 1);
				close(list->outfile);
				j = i;
				while (list->option[j])
				{
					list->option[j] = list->option[j + 2]; //need to check it there is j + 2
					j++;
				}
				continue ;
			}
		}
			i++;
	}
	return (0);
}
