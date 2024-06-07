/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:43:37 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/06/07 01:40:35 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help(t_list *temp, int i)
{
	int		j;
	char	quote;

	j = 0;
	while (temp->option[i][j])
	{
		while (temp->option[i][j] && (temp->option[i][j] != '"' && temp->option[i][j] != '\''))
			j++;
		if (temp->option[i][j] == '"' || temp->option[i][j] == '\'')
		{
			quote = temp->option[i][j++];
			while (temp->option[i][j] != quote && temp->option[i][j])
				temp->option[i][j++] *= -1;
		}
		if (temp->option[i][j] == '\0')
			return ;
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

void    add_back(t_list **list, char *content)
{
    t_list	*node;
    t_list	*temp;

    if (!list)
        return ;
    node = malloc (sizeof(t_list));
    if (!node)
        return ;
    node->option = NULL;
    node->cmd = ft_strdup(content);
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

void    store_cmd(char *input, t_list **list)
{
    char    **s;
    int        i;

    i = 0;
    s = NULL;
    s = ft_split(input, '|');
    if (s == NULL)
        return ;
    while (s[i])
    {
        add_back(list, s[i]);
        free(s[i]);
        i++;
    }
    free(s);
}

void	split_cmd(t_list **list, char *input)
{
	t_list	*temp;
	int		i;

	store_cmd(input, list);
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
