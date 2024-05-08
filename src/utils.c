/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:09:06 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/08 17:59:43 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_env *env, char **cmd)
{
	(void)env;
	if (*cmd)
	{
		if (ft_strncmp(cmd[0], "cd", 2) == 0)
			return(ft_cd(cmd[1]));
		if (ft_strncmp(cmd[0], "pwd", 3) == 0)
			return (ft_pwd());
		if (ft_strncmp(cmd[0], "env", 3) == 0)
			return (ft_env());
	}
	return (0);
}
