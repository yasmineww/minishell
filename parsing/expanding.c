/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:39:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/28 22:25:52 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_new_key(t_list *list, int index, t_mini *mini, int quotes)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (list->option[index][++i])
	{
		if (list->option[index][i] == '"' || list->option[index][i] == '\'')
			mini->is_quote = 1;
		if (list->option[index][i] == '"' && !(quotes & 1))
			quotes = !((quotes >> 1) & 1) << 1;
		else if (list->option[index][i] == '\'' && !((quotes >> 1) & 1))
			quotes = !(quotes & 1);
		else if (list->option[index][i] == '$' && !(quotes & 1))
		{
			if (list->option[index][i + 1] && list->option[index][i + 1] == '$')
			{
				i++;
				continue ;
			}
			else if (found_quest(list->option[index][i + 1], mini, &j) && ++i)
				continue ;
			else if (!list->option[index][i + 1] || !ft_isalpha_num(list->option[index][i + 1]))
			{
				mini->replace[j++] = list->option[index][i];
				continue ;
			}
			i += replace_with_value(list, list->option[index] + i + 1, mini, &j);
			i++;
		}
		else
			mini->replace[j++] = list->option[index][i];
	}
}

int	get_value_len(char *ptr, int j, int end, t_exp *exp)
{
	char	*ptr2;

	ptr2 = ft_substr(ptr, j, end);
	if (!ptr2)
		return (0);
	while (exp)
	{
		if (!ft_strcmp(exp->key, ptr2))
		{
			free(ptr2);
			return (ft_strlen(exp->value));
		}
		exp = exp->next;
	}
	free(ptr2);
	return (0);
}

int	helper2(char *tmp, t_mini *mini)
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
			mini->list->flags.expanded = 1;
			if (tmp[j + 1] && tmp[j + 1] == '?')
				len += ft_intlen(mini->status);
			else
			{
				end = get_key(&tmp[j + 1]);
				len += get_value_len(tmp, j + 1, end, mini->exp);
			}
		}
	}
	return (len);
}

void	rm_empty_option(char ***option, int count)
{
	char	**arr;
	int		j;
	int		i;

	i = 0;
	j = 0;
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return ;
	arr[count] = NULL;
	while ((*option)[i])
	{
		if ((*option)[i][0] != '\0')
		{
			if ((*option)[i][0] == 1)
				(*option)[i][0] = 0;
			arr[j++] = (*option)[i];
		}
		else
			free((*option)[i]);
		i++;
	}
	free(*option);
	(*option) = arr;
}

void	expanding(t_mini *mini, int i, int count, t_list *tmp)
{
	tmp = mini->list;
	while (tmp)
	{
		i = -1;
		count = 0;
		while (tmp->option[++i])
		{
			mini->is_quote = 0;
			mini->replace = ft_calloc(1, helper2(tmp->option[i], mini) + 1);
			if (!mini->replace)
				return ;
			store_new_key(tmp, i, mini, 0);
			if (tmp->option[i][0] == '"')
				tmp->flags.ambiguous = 0;
			if (*mini->replace != '\0')
				count++;
			if (*mini->replace == '\0' && mini->is_quote && ++count)
				*mini->replace = 1;
			free(tmp->option[i]);
			tmp->option[i] = ft_strdup(mini->replace);
			free(mini->replace);
		}
		rm_empty_option(&tmp->option, count);
		tmp = tmp->next;
	}
}
