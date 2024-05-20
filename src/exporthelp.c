/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporthelp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:47:43 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/19 22:21:20 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*dup_list(t_exp *exp)
{
	t_exp	*head;
	t_exp	*last;

	if (!exp)
		return (NULL);
	head = malloc(sizeof(t_exp));
	if (!head)
		return (NULL);
	last = head;
	while (exp)
	{
		last->key = ft_strdup(exp->key);
		last->value = ft_strdup(exp->value);
		if (exp->next)
		{
			last->next = malloc(sizeof(t_exp));
			if (!last->next)
				return (NULL);
			last = last->next;
		}
		else
			last->next = NULL;
		exp = exp->next;
	}
	return (head);
}

void	swap_values(t_exp *a, t_exp *b)
{
	char	*tmpkey;
	char	*tmpvalue;

	if (!a || !b)
		return ;
	tmpkey = a->key;
	tmpvalue = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmpkey;
	b->value = tmpvalue;
}

void	print_exp(t_exp *exp)
{
	while (exp)
	{
		if (!exp->value)
			printf("declare -x %s\n", exp->key);
		else
			printf("declare -x %s=\"%s\"\n", exp->key, exp->value);
		exp = exp->next;
	}
}

void	sort_list(t_exp *exp)
{
	int		swapped;
	t_exp	*ptr1;
	t_exp	*lptr;
	int		i;

	swapped = 1;
	lptr = NULL;
	i = 0;
	while (swapped)
	{
		swapped = 0;
		ptr1 = exp;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap_values(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
