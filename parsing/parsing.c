/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:27:34 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/24 16:17:52 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(char *input, t_list **list)
{
	t_list	*temp;

	if (quotes_syntax_error(input) || syntax_error(input))
	{
		error_message(input);
		return ;
	}
	input = add_space(input);
	split_cmd(list, input);
	temp = *list;
	// while (temp)
	// {
	// 	printf("node.cmd : %s\n", temp->cmd);
	// 	int i = -1;
	// 	while (temp->option[++i])
	// 		printf("node.option[%i] : %s\n",i,temp->option[i]);
	// 	temp = temp->next;
	// 	puts("--------------------------------------");
	// }
}
