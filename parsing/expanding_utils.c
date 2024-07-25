/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:26:36 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/24 20:29:15 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	found_quest(char node, t_mini *mini, int *j)
{
	char	*value;

	if (node == '?')
	{
		value = ft_itoa(mini->status);
		while (*value)
		{
			mini->replace[(*j)++] = *value;
			value++;
		}
		return (1);
	}
	return (0);
}

int	store_dollar(char *node, char *replace, int i)
{
	int	j;

	j = 0;
	if ((check_space(&node[i + 1]) || node[i + 1] == '\0'))
	{
		replace[j] = node[i];
		return (1);
	}
	return (0);
}

int	replace_with_value(t_list *list, char *node, t_mini *mini, int *j)
{
	int		end;
	char	*value;

	end = get_key(node);
	value = get_value(node, end, mini->exp);
	if (end == 0 || !value)
		list->flags.ambiguous = 1;
	if (value)
	{
		if (count_word_spaces(value) > 1)
			list->flags.special = 1;
		while (*value)
		{
			mini->replace[*j] = *value;
			(*j)++;
			value++;
		}
	}
	return (end - 1);
}

char	*get_value(char *ptr, int end, t_exp *exp)
{
	char	*ptr2;

	ptr2 = ft_substr(ptr, 0, end);
	if (!ptr2)
		return (NULL);
	while (exp)
	{
		if (!ft_strcmp(exp->key, ptr2))
		{
			free(ptr2);
			return (exp->value);
		}
		exp = exp->next;
	}
	free(ptr2);
	return (NULL);
}

int	get_key(char *ptr)
{
	int	i;

	i = 0;
	while (ft_isalpha_num(ptr[i]))
		i++;
	return (i);
}
