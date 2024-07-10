/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:32:53 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/09 22:51:54 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(char **cmd)
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
			exit(atoi(cmd[1]));// replace with my atoi
		else
			return (ft_error("exit", cmd[1], "numeric argument required"), exit(2), 1);
	}
	if (i > 2)
	{
			if (!ft_isnumber(cmd[1]))
				return (ft_error("exit", cmd[1], "numeric argument required"), exit(2), 1);
			else
				return (ft_error("exit", NULL, "too many arguments"), 1);
	}
	return (write(2, "exit\n", 5), ft_error("exit", NULL, "too many arguments"), exit(1), 1);
}
