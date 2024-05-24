/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:39:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/23 17:15:14 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*store_new_key(char *node, int len, t_exp **exp)
{
	int		i;
	int		j;
	int		end;
	char	*replace;
	char	*value;

	i = -1;
	j = 0;
	replace = calloc (1, len + 1);
	if (!replace)
		return NULL;
	while (node[++i])
	{
		if (node[i] == '$' && node[0] != '\'')
		{
			i++;
			end = get_key(&node[i]);
			value = get_value(&node[i], end, exp);
			if (value)
			{
				while (*value)
				{
					replace[j++] = *value;
					value++;
				}
			}
			i += end - 1;
		}
		else if (node[i] == '"' || node[i] == '\'')
			continue ;
		else
			replace[j++] = node[i];
	}
	return (replace);
}

int	get_value_len(char *ptr, int j, int end, t_exp **exp)
{
	char	*ptr2;
	t_exp	*env;

	env = *exp;
	ptr2 = ft_substr(ptr, j, end);
	if (!ptr2)
		return 0;
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

	len = ft_strlen(tmp);
	j = -1;
	while (tmp[++j])
	{
		if (tmp[j] == '$')
		{
			end = get_key(&tmp[j + 1]);
			len += get_value_len(tmp, j + 1, end, exp);
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
