/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/11 16:08:20 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_ambiguous(char *s, char *val)
{
	int	i;

	i = 0;
	while(s[i])
	{
		if (check_space(&s[i]) && val)
			return (ft_error("bash: ", s, " ambiguous redirect"), 1);// exit status to 1
		i++;
	}
	return (0);
}

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

void	handle_redirs(t_list *list)
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
			handle_append(list, i);
		else if (list->option[i] && !ft_strncmp(list->option[i], ">", 1))
			handle_redir_out(list, i);
		else if (list->option[i] && !ft_strncmp(list->option[i], "<", 1))
			handle_redir_in(list, i);
		i++;
	}
}

void	handle_redir_in(t_list *list, int i)
{
	list->infile = -1;
	if (list->option[i + 1])
	{
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
}

int	handle_redir_out(t_list *list, int i)
{
	list->outfile = -1;
	if (list->option[i + 1])
	{
		char *val = getenv(list->option[i + 1]);
		if (val)
			check_ambiguous(list->option[i + 1], val);
		else
			return (ft_error("bash: ", list->option[i + 1], " ambiguous redirect"), exit(1), 1); // exit status to 1
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

void	handle_append(t_list *list, int i)
{
	list->outfile = -1;
	if (list->option[i + 1])
	{
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
}
