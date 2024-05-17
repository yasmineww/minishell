/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:43:37 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/16 21:59:59 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back_spaces(t_list **stack_a, char **content)
{
	t_list	*node;
	t_list	*temp;

	node = malloc (sizeof(t_list));
	if (!node)
		return ;
	node->command = content;
	node->next = NULL;
	if ((*stack_a) == NULL)
	{
		*stack_a = node;
		return ;
	}
	temp = *stack_a;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = node;
}

void	split_cmd(t_list **list)
{
	t_list	*temp;

	temp = *list;
	while (temp)
	{
		temp->command = ft_split_spaces(temp->cmd);
		temp = temp->next;
	}
}
