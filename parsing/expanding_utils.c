/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:26:36 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/11 18:17:20 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	found_question_mark(char node, t_exp **exp, char *replace)
{
	char	*value;
	int		j;

	j = 0;
	if (node == '?')
	{
		value = ft_itoa((*exp)->status);
		while (*value)
		{
			replace[j++] = *value;
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

int	replace_with_value(char *node, t_exp **exp, char *replace, int *i)
{
	int		end;
	char	*value;
	int		j;

	j = 0;
	if (node[*i] == '$')
		return (1);
	end = get_key(&node[*i]);
	value = get_value(&node[*i], end, exp);
	if ((end == 0 || !value) && node[*i] != '\'' && node[*i] != '"')
		(*exp)->ambiguous = 1;
	if (value)
	{
		if (count_word_spaces(value) > 1)
			(*exp)->ambiguous = 1;
		while (*value)
		{
			replace[j] = *value;
			j++;
			value++;
		}
	}
	*i += end - 1;
	return (0);
}

char	*get_value(char *ptr, int end, t_exp **exp)
{
	char	*ptr2;
	t_exp	*env;

	env = *exp;
	ptr2 = ft_substr(ptr, 0, end);
	if (!ptr2)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, ptr2))
		{
			free(ptr2);
			return (env->value);
		}
		env = env->next;
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
