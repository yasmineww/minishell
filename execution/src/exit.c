/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:32:53 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/11 12:18:45 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(char **cmd , t_exp *exp)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		exit(0);
	if (i == 2)
	{
		if (ft_isnumber(cmd[1]))
			exit(my_atoi(cmd[1]));// replace with my atoi
		else
			return (ft_error("exit", cmd[1], "numeric argument required"), exit(255), 1);
	}
	if (i > 2)
	{
			if (!ft_isnumber(cmd[1]))
				return (ft_error("exit", cmd[1], "numeric argument required"), exit(255), 1);
			else
				return (ft_error("exit", NULL, "too many arguments"), exp->status = 1, 1);
	}
	return (exp->status = 1, 1);
}
