/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:27:34 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/06/10 22:49:27 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(char *input, t_list **list)
{
	t_list	*temp;
	char	*tmp;

	tmp = input;
	while ((*tmp >= 9 && *tmp <= 13) || *tmp == 32)
		tmp++;
	if (!*tmp)
		return ;
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
	// 	puts("ok");
	// 	printf("node.cmd : %s\n", temp->cmd);
	// 	int i = -1;
	// 	while (temp->option[++i])
	// 		printf("node.option[%i] : %s\n",i,temp->option[i]);
	// 	temp = temp->next;
	// 	puts("--------------------------------------");
	// }
}
