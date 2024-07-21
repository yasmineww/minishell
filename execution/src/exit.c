/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:32:53 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/21 22:06:35 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(char **cmd, t_exp *exp)
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
			exit(my_atoi(cmd[1]));
		else
			return (ft_error("exit", cmd[1],
					"numeric argument required\n"), exit(255), 1);
	}
	if (i > 2)
	{
		if (!ft_isnumber(cmd[1]))
			return (ft_error("exit", cmd[1],
					"numeric argument required\n"), exit(255), 1);
		else
			return (ft_error("exit", NULL,
					"too many argument\n"), exp->status = 1, 1);
	}
	return (exp->status = 1, 1);
}
