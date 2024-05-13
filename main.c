/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/13 23:59:05 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_back(t_list **stack_a, char **content)
{
    t_list    *node;
    t_list    *temp;

    node = malloc (sizeof(t_list));
    if (!node)
        return ;
    node->cmd = content;
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

void    store_cmd(char *input, t_list **list)
{
    char    **s;
    int        i;

    i = 0;
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

int    main ()
{
    char    *input;
    t_list    *list;
    // int i = 0;

    list = malloc(sizeof(t_list *));
    if (!list)
        return (1);
	list = NULL;
    while (1)
    {
        input = readline("Minishell$ ");
        add_history(input);
        syntax_error(input);
        store_cmd(input, &list);
		t_list *current = list;
		while (current)
		{
			printf("cmd is %s\n", current->cmd[0]);
			current = current->next;
		}
		free(input);
    }
}
