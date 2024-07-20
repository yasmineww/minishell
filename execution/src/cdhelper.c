/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdhelper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:51:53 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/20 19:00:40 by ymakhlou         ###   ########.fr       */
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
			// if(exp->value) ymkn 7it katfreeya list flkhr dakchi 3lach double free idan solution hia oldpwd w pwd nt7km fihom ana
				// free(exp->value);
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

int	find_home(t_exp *exp)
{
	int	ret;

	if (exp->value == NULL)
		return (exp->status = 1,
			ft_error("Minishell: cd:", "HOME not set", NULL), 1);
	ret = chdir(exp->value);
	if (ret)
		return (ft_error("Minishell: cd:", exp->value,
				"No such file or directory"), exp->status = 1, 1);
	if (exp->pwd)
		free(exp->pwd);
	exp->pwd = ft_strdup(exp->value);
	return (0);
}

int	ft_find_home(t_exp *exp)
{
	int	res;

	while (exp)
	{
		if (ft_strcmp(exp->key, "HOME") == 0)
		{
			res = find_home(exp);
			if (res == 0)
				return (exp->status = 0, 0);
			return (res);
			// else // wa9ila break 7sn
				// break ;
		}
		exp = exp->next;
	}
	return (exp->status = 1,
		ft_error("Minishell: cd:", "HOME not set", NULL), 1);
}
