/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:04:17 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/22 18:10:45 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_delimiter(t_list *temp, int i)
{
	int		fd;
	char	*read;

	fd = open("/tmp/.here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	temp->heredoc = fd;
	if (fd == -1) {
		perror("Failed to open temporary file");
		return ;
	}
	read = readline("> ");
	while (read)
	{
		if (read[0] == '\0')
			break ;
		if (!ft_strcmp(temp->option[i + 1], read))
			break ;
		read = readline("> ");
	}
	close(fd);
}

void	handle_heredoc(t_list **list)
{
	t_list	*temp;
	int		i;

	temp = *list;
	while (temp)
	{
		i = 0;
		while (temp->option[i])
		{
			if (!ft_strcmp(temp->option[i], "<<"))
			{
				find_delimiter(temp, i);
				// fd = open("/tmp/.here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
				// temp->fd = fd;
				// if (fd == -1) {
                // 	perror("Failed to open temporary file");
                // 	return ;
				// }
				// read = readline("> ");
				// while (read)
				// {
				// 	if (!ft_strcmp(temp->option[i + 1], read))
				// 		break ;
				// 	read = readline("> ");
				// }
				// close(fd);
			}
			i++;		
		}
		temp = temp->next;
	}
}
