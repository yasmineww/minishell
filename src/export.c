/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:49:21 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/14 15:29:56 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*last_node(t_exp *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}
void	ft_lstadd_back(t_exp **head, t_exp *new)
{
	t_exp	*last;

	if (!head)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	last = last_node(*head);
	last -> next = new;
}
int	export(t_exp **exp, char *s)
{
	t_exp	*new;
	t_exp	*cur;
	int		i;
	int		old_i;

	i = 0;
	cur = *exp;
	if (!s)
	{
		t_exp	*tmp;
		tmp = *exp;
		while (tmp)
		{
			t_exp	*tmp2;
			tmp2 = tmp->next;
			if (tmp2 && ft_strncmp(tmp->key, tmp2->key, 1) > 0)
				printf("declare -x %s=\"%s\"\n", tmp2->key, tmp2->value);
			else if (tmp2)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			tmp = tmp2;
		}
		return (0);
	}
	while (s[i] && (s[i] != '+' || s[i] != '='))
	{
		i++;
		if (s[i] == '+')
		{
			if (s[i + 1] == '=')
			{
				while (cur)
				{
					if (ft_strncmp(cur->key, s, i - 2) == 0)
					{
						cur->value = ft_strjoin(cur->value, s + i + 2);
						return (0);
					}
					cur = cur->next;
				}
			}
		}
		else if (s[i] == '=')
		{
			old_i = i;
			i = 0;
			while (cur)
			{
				if (ft_strncmp(cur->key, s, old_i - 1) == 0)
				{
					cur->value = ft_strdup(s + old_i + 1);
					return (0);
				}
				cur = cur->next;
			}
			new = malloc(sizeof(t_exp));
			if (!new)
				return (-1);
			new->key = ft_substr(s, 0, old_i);
			new->value = ft_strdup(s + old_i + 1);
			new->next = NULL;
			ft_lstadd_back(exp, new);
			return (0);
		}
	}
	return (0);
}
