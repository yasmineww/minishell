/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:04:17 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/06/10 02:45:30 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_delimiter(t_list *temp, t_exp **exp, int i)
{
	static int	num;
	char		*read;
	char		*file;
	int			bool;
	char		*delim;

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
		if (temp->option[i + 1][0] == '$')
			delim = ft_strtrim(temp->option[i + 1] + 1, "\'\"");
		else
			delim = ft_strtrim(temp->option[i + 1], "\'\"");
		printf("delim = %s\n", delim);
		if (!ft_strcmp(delim, read))
		{
			free(delim);
			break ;
		}
		free(delim);
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

void	handle_heredoc(t_list **list, t_exp **exp)
{
	t_list		*temp;
	int			i;
	int			j;

	temp = *list;
	if (temp)
		temp->infile = 0;
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
