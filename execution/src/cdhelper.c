/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdhelper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:51:53 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/28 20:21:27 by mbenchel         ###   ########.fr       */
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

void	update_value(t_exp *exp, char *val)
{
	if (exp->value)
		free(exp->value);
	exp->value = ft_strdup(val);
}

void	cwd_oldpwd(t_exp *exp, char *cwd, char *oldpwd)
{
	while (exp)
	{
		if (ft_strcmp(exp->key, "PWD") == 0)
			update_value(exp, cwd);
		if (ft_strcmp(exp->key, "OLDPWD") == 0)
		{
			if (oldpwd)
				update_value(exp, oldpwd);
			else
				update_value(exp, cwd);
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
	if (ret == -1)
		return (mini->status = 0, 0);
	if (mini->pwd)
		free(mini->pwd);
	mini->pwd = ft_strdup(exp->value);
	return (0);
}

int	ft_find_home(t_exp *exp, t_mini *mini)
{
	int		res;
	t_exp	*tmp;

	tmp = exp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
		{
			res = find_home(tmp, mini);
			if (res == 0)
				return (mini->status = 0, 0);
			return (res);
		}
		tmp = tmp->next;
	}
	return (mini->status = 1,
		ft_error("Minishell: cd:", "HOME not set\n", NULL), 1);
}
