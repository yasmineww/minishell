/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/31 01:17:05 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void remove_redir(char **option, int i)
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

void handle_redirs(t_list *list)
{
	int i = 0;

	while (list->option[i])
	{
		if (!ft_strncmp(list->option[i], "<<", 2))
		{
			dup2(list->infile, 0);
			close(list->infile);
			remove_redir(list->option, i);
		}
		if (!ft_strncmp(list->option[i], ">>", 2))
			handle_append(list, i);
		else if (!ft_strncmp(list->option[i], ">", 1))
			handle_redir_out(list, i);
		else if (!ft_strncmp(list->option[i], "<", 1))
			handle_redir_in(list, i);
		else
			i++;
	}
}


void	handle_redir_in(t_list *list, int i)
{
	int	j;

	j = 0;
	list->infile = -1;
	if (list->option[i + 1])
	{
		list->infile = open(list->option[i + 1], O_RDONLY);
		if (list->infile == -1)
		{
			perror("open");
			return ;
		}
		dup2(list->infile, 0);
		close(list->infile);
		remove_redir(list->option, i);
	}
}
void	handle_redir_out(t_list *list, int i)
{
	int	j;

	j = 0;
	list->outfile = -1;
	if (list->option[i + 1])
	{
		list->outfile = open(list->option[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (list->outfile == -1)
		{
			perror("open");
			return ;
		}
		dup2(list->outfile, 1);
		close(list->outfile);
		remove_redir(list->option, i);
	}
}

void	handle_append(t_list *list, int i)
{
	int	j;

	j = 0;
	list->outfile = -1;
	if (list->option[i + 1])
	{
		list->outfile = open(list->option[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (list->outfile == -1)
		{
			perror("open");
			return ;
		}
		dup2(list->outfile, 1);
		close(list->outfile);
		remove_redir(list->option, i);
	}
}


