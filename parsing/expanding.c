/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:39:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/11 17:26:16 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*store_new_key(char *node, int len, t_exp **exp)
{
	int		i;
	int		j;
	char	*replace;
	int		in_double_quotes;
	int		in_single_quotes;

	i = -1;
	j = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	replace = ft_calloc(1, len + 1);
	if (!replace)
		return (NULL);
	while (node[++i])
	{
		if (node[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (node[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (node[i] == '$' && !in_single_quotes)
		{
			if (store_dollar(node, &replace[j], i) && j++)
				break ;
			else if (found_question_mark(node[i + 1], exp, &replace[j]) && i++)
				continue ;
			i++;
			if (replace_with_value(node, exp, &replace[j], &i))
				continue ;
		}
		else
			replace[j++] = node[i];
	}
	replace[len] = '\0';
	return (replace);
}

int	get_value_len(char *ptr, int j, int end, t_exp **exp)
{
	char	*ptr2;
	t_exp	*env;

	env = *exp;
	ptr2 = ft_substr(ptr, j, end);
	if (!ptr2)
		return (0);
	while (env)
	{
		if (!ft_strcmp(env->key, ptr2))
			return (ft_strlen(env->value));
		env = env->next;
	}
	return (0);
}

int	helper2(char *tmp, t_exp **exp)
{
	int	len;
	int	j;
	int	end;

	len = 0;
	len = ft_strlen(tmp);
	j = -1;
	while (tmp[++j])
	{
		if (tmp[j] == '$')
		{
			if (tmp[j + 1] && tmp[j + 1] == '?')
				len += ft_intlen((*exp)->status);
			else
			{
				end = get_key(&tmp[j + 1]);
				len += get_value_len(tmp, j + 1, end, exp);
			}
		}
	}
	return (len);
}

void	expanding(t_list **list, t_exp **exp)
{
	int		i;
	int		len;
	t_list	*tmp;
	char	*replace;

	tmp = *list;
	while (tmp)
	{
		i = 0;
		while (tmp->option[i])
		{
			len = helper2(tmp->option[i], exp);
			replace = store_new_key(tmp->option[i], len, exp);
			tmp->option[i] = ft_strdup(replace);
			free(replace);
			i++;
		}
		tmp = tmp->next;
	}
}
