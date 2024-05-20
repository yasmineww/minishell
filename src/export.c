/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:49:21 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/20 16:44:25 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


	// fix export adds another one if the key is already there
// PATH kitprinta w _ makitprintaach


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

int exporthelp(t_exp *exp, char *s, t_flag *flags)
{
	t_exp	*new;

	if (!s)
	{
		if (!flags->sorted_flag)
		{
			new = dup_list(exp);
			sort_list(new);
			print_exp(new);
			flags->sorted_flag = 1;
		}
		else
			print_exp(exp);
	}
	else if (s && exp)
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
	if (s[i] && isalpha_underscore(s[i]) == 0)
		{
			write(2, "bash: export: ", 14);
			write(2, "`", 1);
			write(2, s, ft_strlen(s));
			write(2, "'", 1);
			write(2,": not a valid identifier\n", 25);
			return (1);
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
					new->value = NULL;
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
