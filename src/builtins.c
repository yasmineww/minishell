/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:09:06 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/20 16:38:06 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_exp **exp, char **cmd, char **envp, t_flag *flags)
{
	(void)envp;
	if (*cmd)
	{
		if (ft_strncmp(cmd[0], "cd", 2) == 0)
			return(ft_cd(cmd[1]));
		if (ft_strncmp(cmd[0], "pwd", 3) == 0)
			return (ft_pwd());
		if (ft_strncmp(cmd[0], "env", 3) == 0)
			print_env(exp);
		if (ft_strncmp(cmd[0], "exit", 4) == 0)
			exit(0);
		if (ft_strncmp(cmd[0], "echo", 4) == 0)
			return (ft_echo(cmd));
		if (ft_strncmp(cmd[0], "unset", 5) == 0)
			return (ft_unset(exp, cmd[1]));
		if (ft_strncmp(cmd[0], "export", 6) == 0)
			return (exporthelp(*exp, cmd[1], flags));
	}
	return (0);
}