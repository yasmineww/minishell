/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:09:06 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/20 14:12:59 by mbenchel         ###   ########.fr       */
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
		{
			printf("exit\n");
			return (1);
		}
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

int	ft_2dlen(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	exec_builtin(t_exp **exp, char **cmd, t_list *list)
{
	if (!cmd || !*cmd)
		return (0);
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		if (ft_2dlen(cmd) > 2)
			return (ft_error("Minishell: cd:", "too many arguments",
					NULL), (*exp)->status = 1, 1);
		else
			return (ft_cd(cmd[1], *exp, list));
	}
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd(*exp));
	if (ft_strcmp(cmd[0], "env") == 0)
		print_env(exp);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd, *exp));
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd, *exp));
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset_helper(exp, cmd, list));
	if (ft_strcmp(cmd[0], "export") == 0)
		return (exporthelp(*exp, cmd, list));
	return (0);
}
