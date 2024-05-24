/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/24 21:07:44 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_redir(t_list *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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





//		outf = open(data.output, O_RDWR | O_CREAT | O_TRUNC, 0644);
