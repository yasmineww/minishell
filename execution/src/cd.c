/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:36:55 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/26 20:29:36 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_cwd(t_mini *mini)
{
	char	*cwd;
	char	*oldpwd;
	t_exp	*cur;

	cur = mini->exp;
	oldpwd = ft_getoldpwd(mini->exp);
	cwd = getcwd(NULL, 0);
	cwd_oldpwd(mini->exp, cwd, oldpwd);
	free(cwd);
	if (mini->pwd_unset == 1)
	{
		cur = create_node("PWD", cwd);
		ft_lstadd_back(&mini->exp, cur);
		mini->pwd_unset = 0;
	}
	if (mini->oldpwd_unset == 1)
	{
		cur = create_node("OLDPWD", oldpwd);
		ft_lstadd_back(&mini->exp, cur);
		mini->oldpwd_unset = 0;
	}
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

static int	two_dots(t_mini *mini)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_error("Minishell: cd:", NULL,
			"error in retrieving current directory\n");
		chdir(mini->pwd);
	}
	else
	{
		free(cwd);
		chdir("..");
	}
	return (0);
}

int	ft_cd(char *path, t_mini *mini)
{
	int		ret;

	if (path && path[0] == '\0')
		return (0);
	if (!path)
		ft_find_home(mini->exp, mini);
	else if (!ft_strncmp(path, "..", 2))
		two_dots(mini);
	else
	{
		ret = chdir(path);
		if (ret != 0)
			return (ft_error("Minishell: cd:", path, "No such file or directory\n")
				, mini->status = 1, 1);
	}
	update_cwd(mini);
	mini->status = 0;
	return (0);
}
