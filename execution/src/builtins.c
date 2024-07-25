/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:09:06 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/24 13:18:05 by mbenchel         ###   ########.fr       */
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

int	exec_builtin(t_mini *mini, char **cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		if (ft_2dlen(cmd) > 2)
			return (ft_error("Minishell: cd:", "too many arguments\n",
					NULL), mini->status = 1, 1);
		else
			return (ft_cd(cmd[1], mini));
	}
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd(mini));
	if (ft_strcmp(cmd[0], "env") == 0)
		print_env(&mini->exp);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd, mini));
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd, mini->exp, mini));
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset_helper(mini, cmd));
	if (ft_strcmp(cmd[0], "export") == 0)
		return (exporthelp(mini, cmd));
	return (0);
}
