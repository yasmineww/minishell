/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:09:10 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/20 17:29:10 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset_helper(t_exp **exp, char **s, t_list *list)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (ft_strchr(s[i], '=') || !isalpha_underscore(s[i][0], 1))
		{
			ft_error("minishell: unset: `", s[i], "': not a valid identifier");
			(*exp)->status = 1;
			i++;
			continue ;
		}
		ft_unset(exp, s[i], list);
		i++;
	}
	return (0);
}

int	ft_unset(t_exp **exp, char *key, t_list *list)
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
			if (!ft_strncmp(cur->key, "PWD", 3))
				list->pwd_unset = 1;
			if (!ft_strncmp(cur->key, "OLDPWD", 6))
				list->oldpwd_unset = 1;
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
