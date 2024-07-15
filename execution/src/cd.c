/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:36:55 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/13 19:54:02 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_cwd(t_exp *exp)
{
	char	*cwd;
	char	*oldpwd;

	oldpwd = ft_getoldpwd(exp);
	cwd = getcwd(NULL, 0);
	cwd_oldpwd(exp, cwd, oldpwd);
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
