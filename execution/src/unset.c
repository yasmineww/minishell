/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:09:10 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/15 23:44:20 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset_helper(t_exp *exp, char **s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (ft_strchr(s[i], '='))
		{
			ft_error("minishell: unset: `", s[i], "': not a valid identifier");
			exp->status = 1;
			i++;
			continue ;
		}
		ft_unset(&exp, s[i]);
		i++;
	}
	return (0);
}

int	ft_unset(t_exp **exp, char *key)
{
	t_exp	*cur;
	t_exp	*prev;

	cur = *exp;
	prev = NULL;
	if (!key)
		return ((*exp)->status = 1, 1);
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key)) == 0)
		{
			if (!prev)
				*exp = cur->next;
			else
				prev->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
