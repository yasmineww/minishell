/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:09:10 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/26 20:26:30 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset_helper(t_mini *mini, char **s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (ft_strchr(s[i], '=') || !isalpha_underscore(s[i][0], 1))
		{
			ft_error("minishell: unset: `", s[i], \
				"': not a valid identifier\n");
			mini->status = 1;
			i++;
			continue ;
		}
		ft_unset(mini, s[i]);
		i++;
	}
	return (0);
}

void	free_exp_node(t_exp *exp)
{
	free(exp->key);
	free(exp->value);
	free(exp);
}

void	unset_flags(t_mini *mini, t_exp *cur)
{
	if (!ft_strncmp(cur->key, "PWD", 3))
		mini->pwd_unset = 1;
	if (!ft_strncmp(cur->key, "OLDPWD", 6))
		mini->oldpwd_unset = 1;
}

int	ft_unset(t_mini *mini, char *key)
{
	t_exp	*cur;
	t_exp	*prev;

	cur = mini->exp;
	prev = NULL;
	if (!key)
		return (mini->status = 1, 1);
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key)) == 0)
		{
			unset_flags(mini, cur);
			if (!prev)
				mini->exp = cur->next;
			else
				prev->next = cur->next;
			free_exp_node(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
