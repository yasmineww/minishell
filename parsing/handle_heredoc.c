/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:04:17 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/06/09 21:06:33 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_delimiter(t_list *temp, t_exp **exp, int i)
{
	static int	num;
	char		*read;
	char		*file;
	int			bool;
	char		*ptr;

	bool = 0;
	if (temp->option[i + 1][0]== '"' || temp->option[i + 1][0]== '\'')
		bool = 1;
	file = ft_strjoin(".here_doc", ft_itoa(num++));
	temp->infile = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (temp->infile == -1) {
		perror("Failed to open file");
		free(file);
		return ;
	}
	read = readline("> ");
	while (read)
	{
		if (!bool)
			expanding_heredoc(&read, exp);
		ptr = ft_strtrim(temp->option[i + 1], "\'\"");
		if (!ft_strcmp(ptr, read))
		{
			free(ptr);
			break ;
		}
		free(ptr);
		ft_putendl_fd(read, temp->infile);
		free(read);
		read = readline("> ");
	}
	free(read);
	close(temp->infile);
	temp->infile = open(file, O_RDONLY, 0644);
	if (temp->infile == -1) {
		perror("Failed to open file");
		unlink(file);
		free(file);
		return ;
	}
	unlink(file);
	free(file);
}

void	tmp_file(char *delim)
{
    char        *read;

    read = readline("> ");
    while (read)
    {
		if (!ft_strcmp(delim, read))
			break ;
        free(read);
        read = readline("> ");
    }
    free(read);
}

int	store_delim(t_list **list, t_here_doc *var)
{
	t_list		*temp;
	int			i;
	int			j;
	int			count;

	temp = *list;
	count = 0;
	j = 0;
	var->delimiter = malloc(sizeof(char *) * 100);////// count delimiters
	while (temp)
	{
		i = 0;
		while (temp->option[i] && temp->option[i + 1])
		{
			if (!ft_strcmp(temp->option[i], "<<"))
			{
				var->delimiter[j] = ft_strtrim(temp->option[i + 1], "\'\"");
				count++;
				j++;
			}
			i++;
		}

		temp = temp->next;
	}
	return (count);
}

void	handle_heredoc(t_list **list, t_exp **exp)
{
	t_list		*temp;
	t_here_doc	*var;
	int			i;
	int			j;
	int			count;

	temp = *list;
	temp->infile = 0;
	var = malloc(sizeof(t_here_doc));
	///protect malloc
	count = store_delim(list, var);
	j = 0;
	while (temp)
	{
		i = 0;
		while (temp->option[i])
		{
			if (!ft_strcmp(temp->option[i], "<<"))
				find_delimiter(temp, exp, i);
			i++;
		}
		temp = temp->next;
	}
}
