/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:43:37 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/18 16:01:54 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help(t_list *temp, int i)
{
	int		j;
	char	quote;

	j = 0;
	while (temp->option[i][j])
	{
		while (temp->option[i][j] && (temp->option[i][j] != '"' && temp->option[i][j] != '\''))
			j++;
		if (temp->option[i][j] != '"' || temp->option[i][j] != '\'')
		{
			quote = temp->option[i][j++];
			while (temp->option[i][j] != quote && temp->option[i][j])
				temp->option[i][j++] *= -1;
		}
		j++;
	}
}

void	add_back_spaces(t_list **stack_a, char **content)
{
	t_list	*node;
	t_list	*temp;

	node = malloc (sizeof(t_list));
	if (!node)
		return ;
	node->option = content;
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
	int		i;

	i = 0;
	temp = *list;
	while (temp)
	{
		temp->option = ft_split_spaces(temp->cmd);
		temp = temp->next;
	}
	temp = *list;
	while (temp)
	{
		i = 0;
		while (temp->option[i])
		{
			help(temp, i);
			i++;
		}
		temp = temp->next;
	}
}
