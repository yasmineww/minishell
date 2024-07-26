/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdhelper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:51:53 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/26 20:15:23 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getoldpwd(t_exp *exp)
{
	while (exp)
	{
		if (!ft_strncmp(exp->key, "PWD", 3))
		{
			if (exp->value)
				return (ft_strdup(exp->value));
			else
				return (NULL);
		}
		exp = exp->next;
	}
	return (NULL);
}

void	cwd_oldpwd(t_exp *exp, char *cwd, char *oldpwd)
{
	while (exp)
	{
		if (ft_strcmp(exp->key, "PWD") == 0)
		{
			if (exp->value)
				free(exp->value);
			exp->value = ft_strdup(cwd);
		}
		if (ft_strcmp(exp->key, "OLDPWD") == 0)
		{
			if (oldpwd)
			{
				if (exp->value)
					free(exp->value);
				exp->value = oldpwd;
			}
			else
			{
				if (exp->value)
					free(exp->value);
				exp->value = ft_strdup(cwd);
			}
			oldpwd = NULL;
		}
		exp = exp->next;
	}
}

int	find_home(t_exp *exp, t_mini *mini)
{
	int	ret;

	if (exp->value == NULL)
		return (mini->status = 1,
			ft_error("Minishell: cd:", "HOME not set\n", NULL), 1);
	ret = chdir(exp->value);
	if (ret)
		return (ft_error("Minishell: cd:", exp->value,
				"No such file or directory\n"), mini->status = 1, 1);
	if (mini->pwd)
		free(mini->pwd);
	mini->pwd = ft_strdup(exp->value);
	return (0);
}

int	ft_find_home(t_exp *exp, t_mini *mini)
{
	int		res;
	t_exp 	*tmp;

	tmp = exp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
		{
			res = find_home(tmp, mini);
			if (res == 0)
				return (mini->status = 0, 0);
			return (res);
			// else // wa9ila break 7sn
				// break ;
		}
		tmp = tmp->next;
	}
	return (mini->status = 1,
		ft_error("Minishell: cd:", "HOME not set\n", NULL), 1);
}
