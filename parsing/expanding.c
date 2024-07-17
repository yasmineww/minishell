/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:39:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/17 15:04:12 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_new_key(char *node, t_exp **exp, char *replace, int quotes)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (node[++i])
	{
		if (node[i] == '"' && !(quotes & 1))
			quotes = !((quotes >> 1) & 1) << 1;
		else if (node[i] == '\'' && !((quotes >> 1) & 1))
			quotes = !(quotes & 1);
		else if (node[i] == '$' && !(quotes & 1))
		{
			if (store_dollar(node, &replace[j], i) && j++)
				break ;
			else if (found_question_mark(node[i + 1], exp, replace, &j))
			{
				i++;
				continue ;
			}
			else if (node[++i] == '$')
				continue ;
			i += replace_with_value(node + i, exp, replace, &j);
		}
		else
			replace[j++] = node[i];
	}
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
			(*exp)->expanded = 1;
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
			replace = ft_calloc(1, len + 1);
			if (replace)
				store_new_key(tmp->option[i], exp, replace, 0);
			if (tmp->option[i][0] == '"')
				(*exp)->ambiguous = 0;
			tmp->option[i] = ft_strdup(replace);
			free(replace);
			i++;
		}
		tmp = tmp->next;
	}
}
