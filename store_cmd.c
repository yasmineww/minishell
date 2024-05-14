/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:43:14 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/14 18:10:07 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_list **stack_a, char **content)
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
        add_back(list, &s[i]);
        i++;
    }
    free(s);
}
