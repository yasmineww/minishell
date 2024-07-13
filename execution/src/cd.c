/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:36:55 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/11 18:48:42 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_getcwd(t_exp *exp)
{
	while (exp)
	{
		if (ft_strcmp(exp->key, "PWD") == 0)
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

static void	cwd_oldpwd(t_exp *exp, char *cwd, char *oldpwd)

void	update_cwd(t_exp *exp)
{
	char	*cwd;
	char	*oldpwd;
	t_exp	*tmp;

	oldpwd = NULL;
	cwd = getcwd(NULL, 0);
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
			exp->value = ft_strdup(cwd);
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
	free(cwd);
	if (oldpwd)
		free(oldpwd);
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
static int	find_home(t_exp *exp)
{
	int	ret;

	if (exp->value == NULL)
		return (exp->status = 1,
			ft_error("bash: cd:", "HOME not set", NULL), 1);
	ret = chdir(exp->value);
	if (ret)
		return (ft_error("bash: cd:", exp->value,
				"No such file or directory"), exp->status = 1, 1);
	exp->pwd = ft_strdup(exp->value);
	// if (exp->pwd && ret == 0)
				// 	free(exp->pwd);
	return (0);
}

static int	ft_find_home(t_exp *exp)
{
	int	res;

	while (exp)
	{
		if (ft_strcmp(exp->key, "HOME") == 0)
		{
			res = find_home(exp);
			if (res == 0)
				return (update_cwd(exp), exp->status = 0, 0);
			return (res);
		}
		exp = exp->next;
	}
	return (exp->status = 1,
		ft_error("bash: cd:", "HOME not set", NULL), 1);
}

int	ft_cd_home(t_exp *exp)
{
	return (ft_find_home(exp));
}

static int	two_dots(t_exp *exp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_error("bash: cd:", NULL,
			"error in retrieving current directory");
		chdir(exp->pwd);
	}
	else
	{
		free(cwd);
		chdir("..");
	}
	return (0);
}

int	ft_cd(char *path, t_exp *exp)
{
	int		ret;

	if (!path || path[0] == '\0')
		return (ft_cd_home(exp));
	else if (!ft_strncmp(path, "..", 2))
		return (two_dots(exp));
	else
	{
		ret = chdir(path);
		if (ret != 0)
			return (ft_error("bash: cd:", path, "No such file or directory")
				, exp->status = 1, 1);
	}
	update_cwd(exp);
	exp->status = 0;
	return (0);
}
