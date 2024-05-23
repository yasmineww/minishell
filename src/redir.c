/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/23 22:43:25 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_redir(t_list *list, char **s)
// {
// while (list->option[i])
// 		{
// 			if (!ft_strncmp(list->option[i], "<", 1))
// 			{
// 				if (list->option[i + 1])
// 				{
// 					inf = open(list->option[i + 1], O_RDONLY);
// 					if (inf == -1)
// 					{
// 						perror("open");
// 						break ;
// 					}
// 					dup2(inf, 0);
// 					close(inf);
// 					j = i;
// 					while (list->option[j])
// 					{
// 						list->option[j] = list->option[j + 2];
// 						j++;
// 					}
// 					continue ;
// 				}
// 				else
// 					inf = dup(std_in);
// 			}
// 				i++;
// 		}
// }
//		outf = open(data.output, O_RDWR | O_CREAT | O_TRUNC, 0644);
