/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:49:21 by mbenchel          #+#    #+#             */
/*   Updated: 2024/06/12 20:08:11 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	exporthelp(t_exp *exp, char **s)
{
	t_exp	*new;
	int		i;

	i = 1;
	if (!s[1])
	{
		new = dup_list(exp);
		sort_list(new);
		print_exp(new);
	}
	else if (s[1] && exp)
	{
		while (s[i])
		{
			export(&exp, s[i]);
			i++;
		}
	}
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
	if (s[i] && !isalpha_underscore(s[i], 1)) // mnb3d an7taj nzid ta lquotes 7it atb9a tsifthom
		return (ft_error("export", s, "not a valid identifier"), 1);
	while (s[i] && (s[i] != '+' || s[i] != '='))
	{
		if (s[i] && !isalpha_underscore(s[i], 0))
			return (ft_error("export", s, "not a valid identifier"), 1);
		i++;
		if (s[i] == '+')
		{
			i++;
			if (s[i] == '=')
			{
				while (cur)
				{
					if (ft_strncmp(cur->key, s, i - 2) == 0)
					{
						cur->value = ft_strjoin(cur->value, s + i + 1);
						return (0);
					}
					else
					{
						while (cur)
						{
							if (ft_strncmp(cur->key, s, i - 2) == 0)
							{
								cur->value = ft_strjoin(cur->value, s + i + 1);
								return (0);
							}
							cur = cur->next;
						}
						new = malloc(sizeof(t_exp));
						if (!new)
							return (-1);
						new->key = ft_substr(s, 0, i - 1);
						new->value = ft_strdup(s + i + 1);
						new->next = NULL;
						ft_lstadd_back(exp, new);
						return (0);
					}
					cur = cur->next;
				}
			}
			else
				return (ft_error("export", s, "not a valid identifier"), 1);
		}
		else if (s[i] == '=')
		{
			old_i = i;
			i = 0;
			while (cur)
			{
				if (ft_strncmp(cur->key, s, old_i - 1) == 0 && cur->key[old_i] == '\0')
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
				cur = cur->next;
			}
			new = malloc(sizeof(t_exp));
			if (!new)
				return (-1);
			new->key = ft_strdup(s);
			new->value = NULL;
			new->next = NULL;
			ft_lstadd_back(exp, new);
			return (0);
		}
	}
	return (0);
}
