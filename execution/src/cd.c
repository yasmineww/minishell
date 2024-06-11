/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:36:55 by mbenchel          #+#    #+#             */
/*   Updated: 2024/06/11 23:53:51 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_cwd(t_exp *exp)
{
	char	*cwd;
	char	*oldpwd;
	t_exp	*tmp;

	oldpwd = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_error("bash: cd:", NULL, "error in retrieving current directory");
		return ;
	}
	tmp = exp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			if (tmp->value)
				oldpwd = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	while (exp)
	{
		if (ft_strcmp(exp->key, "PWD") == 0)
		{
			free(exp->value);
			exp->value = cwd;
		}
		if (ft_strcmp(exp->key, "OLDPWD") == 0)
		{
			free(exp->value);
			if (oldpwd)
				exp->value = oldpwd;
			else
				exp->value = ft_strdup(cwd);
		}
		exp = exp->next;
	}
	if (!oldpwd)
		free(cwd);
	// free(cwd);
	// free(oldpwd);
}

void	ft_error(char *str1, char *str2, char *str3)
{
	if (str1)
		write(2, str1, ft_strlen(str1));
	if (str2)
	{
		write(2, " ", 1);
		write(2, str2, ft_strlen(str2));
	}
	if (str3)
	{
		write(2, ": ", 2);
		write(2, str3, ft_strlen(str3));
	}
	write(1, "\n", 1);
}

int	ft_cd(char *path, t_exp *exp)
{
	int		ret;
	// char	*cwd;
	t_exp	*tmp;

	if (!path || path[0] == '\0')
	{
		tmp = exp;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "HOME") == 0)
			{
				if (chdir(tmp->value) != 0)
				{
					ft_error("bash: cd:", "HOME not set", NULL);
					return (1);
				}
				if (exp->pwd)
					free(exp->pwd);
				exp->pwd = ft_strdup(tmp->value);
			}
			tmp = tmp->next;
		}
	}
	else if (!ft_strncmp(path, "..", 2))
	{
		if (chdir("..") == -1 && !getcwd(NULL, 0))
			chdir("exp->pwd");
		if (chdir("..") != 0)
			return (ft_error("bash: cd:", path, "No such file or directory")
				, 1);
	}
	else
	{
		ret = chdir(path);
		if (ret != 0)
			return (ft_error("bash: cd:", path, "No such file or directory")
				, 1);
	}
	update_cwd(exp);
	/// steps to update the PWD and OLDPWD
	return (0);
}
