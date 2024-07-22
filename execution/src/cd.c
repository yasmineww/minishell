/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:36:55 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/23 00:42:29 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_cwd(t_exp *exp, t_list *list)
{
	(void)list;
	char	*cwd;
	char	*oldpwd;
	t_exp	*cur;

	cur = exp;
	oldpwd = ft_getoldpwd(exp);
	cwd = getcwd(NULL, 0);
	cwd_oldpwd(exp, cwd, oldpwd);
	free(cwd);
	// if (list->pwd_unset == 1)
	// {
	// 	puts("create pwd node");
	// 	cur = create_node("PWD", cwd);
	// 	ft_lstadd_back(&exp, cur);
	// 	list->pwd_unset = 0;
	// }
	// if (list->oldpwd_unset == 1)//unset kolchi
	// {
	// 	puts("create oldpwd node");
	// 	cur = create_node("OLDPWD", oldpwd);
	// 	ft_lstadd_back(&exp, cur);
	// 	list->oldpwd_unset = 0;
	// }
	// free(cwd);
	// if (oldpwd)
	// 	free(oldpwd);
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
}

static int	two_dots(t_exp *exp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_error("Minishell: cd:", NULL,
			"error in retrieving current directory\n");
		chdir(exp->pwd);
	}
	else
	{
		free(cwd);
		chdir("..");
	}
	return (0);
}

int	ft_cd(char *path, t_exp *exp, t_list *list)
{
	int		ret;

	if (!path || path[0] == '\0')
		ft_find_home(exp);
	else if (!ft_strncmp(path, "..", 2))
		two_dots(exp);
	else
	{
		ret = chdir(path);
		if (ret != 0)
			return (ft_error("Minishell: cd:", path, "No such file or directory\n")
				, exp->status = 1, 1);
	}
	update_cwd(exp, list);
	exp->status = 0;
	return (0);
}
