/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:49:21 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/17 20:12:14 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	// khas nzid chi flag wla chihaja lakant ghir lkey manprintich lvalue wla chihaja f print_exp
	// l env kitkhrb9 mora makandir export
	// fix export adds another one if the key is already there

void	print_exp(t_exp exp)
{
	t_exp	*head = &exp;
	int i = 0;
	while (head)
	{
		if (!head->value)
			printf("declare -x %s\n", head->key);
		else
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		head = head->next;
		i++;
	}
	// {
	// 	if (!exp->value)
	// 		printf("declare -x %s\n", exp->key);
	// 	else
	// 		printf("declare -x %s=\"%s\"\n", exp->key, exp->value);
	// 	exp = exp->next;
	// }
}

void	swap_values(t_exp *a, t_exp *b)
{
	// char	*swap_key;
	// char	*swap_value;
	t_exp *tmp = (t_exp *)malloc(sizeof(t_exp));

	// if (!a || !b)
	// 	return ;
	tmp->key = a->key;
	tmp->value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp->key;
	b->value = tmp->value;
}

void	sort_list(t_exp exp)
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
		ptr1 = &exp;
		while (ptr1->next != NULL)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap_values(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		// lptr = ptr1;
	}
	print_exp(exp);
}


// void	sort(t_exp exp)
// {
// 	t_exp	*head;
// 	t_exp	*tmp;

// 	tmp = &exp;
// 	head = &exp;

// 	while(tmp && tmp->next)
// 	{
// 		if (ft_strcmp(tmp->key, tmp->next->key) > 0)
// 		{
// 			swap_values(tmp, tmp->next);
// 			tmp = head;
// 		}
// 		else
// 			tmp = tmp->next;
// 	}
// 	print_exp(head);
// }



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
	last->next = new;
}

int exporthelp(t_exp *exp, char *s)
{
	if (!s && exp)
		sort_list(*exp);
		// sort(*exp);
	else if (s)
		export(&exp, s);
	return (0);
}

int	export(t_exp **exp, char *s)
{
	t_exp	*new;
	t_exp	*cur;
	int		i;
	int		old_i;

	i = 0;
	cur = *exp;
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
		else if (!ft_strchr(s, '=') && !ft_strchr(s, '+'))
		{
			while (cur)
			{
				if (ft_strcmp(cur->key, s) == 0)
					return (0);
				else
				{
					new = malloc(sizeof(t_exp));
					if (!new)
						return (-1);
					new->key = ft_strdup(s);
					new->next = NULL;
					ft_lstadd_back(exp, new);
					return (0);
				}
				cur = cur->next;
			}
		}
	}
	return (0);
}
