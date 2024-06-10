/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:09:06 by mbenchel          #+#    #+#             */
/*   Updated: 2024/06/10 14:25:13 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (ft_strcmp(cmd[i], "cd") == 0)
			return (1);
		if (ft_strcmp(cmd[i], "pwd") == 0)
			return (1);
		if (ft_strcmp(cmd[i], "env") == 0)
			return (1);
		if (ft_strcmp(cmd[i], "exit") == 0)
			return (1);
		if (ft_strcmp(cmd[i], "echo") == 0)
			return (1);
		if (ft_strcmp(cmd[i], "unset") == 0)
			return (1);
		if (ft_strcmp(cmd[i], "export") == 0)
			return (1);
		i++;
	}
	return (0);
}
// int	is_builtin(char **cmd)
// {
// 	if (*cmd)
// 	{
// 		if (ft_strcmp(cmd[0], "cd") == 0)
// 			return (1);
// 		if (ft_strcmp(cmd[0], "pwd") == 0)
// 			return (1);
// 		if (ft_strcmp(cmd[0], "env") == 0)
// 			return (1);
// 		if (ft_strcmp(cmd[0], "exit") == 0)
// 			return (1);
// 		if (ft_strcmp(cmd[0], "echo") == 0)
// 			return (1);
// 		if (ft_strcmp(cmd[0], "unset") == 0)
// 			return (1);
// 		if (ft_strcmp(cmd[0], "export") == 0)
// 			return (1);
// 	}
// 	return (0);
// }

int	exec_builtin(t_exp **exp, char **cmd)
{
	if (*cmd)
	{
		if (ft_strcmp(cmd[0], "cd") == 0)
			return (ft_cd(cmd[1], *exp));
		if (ft_strcmp(cmd[0], "pwd") == 0)
			return (ft_pwd());
		if (ft_strcmp(cmd[0], "env") == 0)
			print_env(exp);
		if (ft_strcmp(cmd[0], "exit") == 0)
			exit(0);
		if (ft_strcmp(cmd[0], "echo") == 0)
			return (ft_echo(cmd));
		if (ft_strcmp(cmd[0], "unset") == 0)
			return (ft_unset(exp, cmd[1]));
		if (ft_strcmp(cmd[0], "export") == 0)
			return (exporthelp(*exp, cmd));
	}
	return (0);
}
