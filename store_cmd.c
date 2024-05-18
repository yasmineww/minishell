/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:43:14 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/18 16:01:32 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_list **list, char *content)
{
	t_list	*node;
	t_list	*temp;

	node = malloc (sizeof(t_list));
	if (!node)
		return ;
	node->option = NULL;
	node->cmd = content;
	node->next = NULL;
	if ((*list) == NULL)
	{
		*list = node;
		return ;
	}
	temp = *list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = node;
}

void	store_cmd(char *input, t_list **list)
{
	char	**s;
	int		i;

	i = 0;
	s = NULL;
	s = ft_split(input, '|');
	if (s == NULL)
		return ;
	while (s[i])
	{
		add_back(list, s[i]);
		i++;
	}
	free(s);
}
