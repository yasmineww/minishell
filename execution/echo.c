/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:27:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/10 21:05:31 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd)
{
	int	params;
	int	i;
	int	no_nl;

	i = 1;
	no_nl = 0;
	params = countparams(cmd);
	if (params > 1 && ft_strncmp(cmd[1], "-n", 2) == 0)
		no_nl = 1;
	while (i < params)
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			if (i + 1 < params)
			{
				if (cmd[i + 1] && cmd[i + 1][0] == '-')
					if (ft_strncmp(cmd[i + 1], "-n", 2) != 0)
						no_nl = 1;
			}
		}
		else
		{
			if (i == params - 1)
				printf("%s", cmd[i]);
			else
				printf("%s ", cmd[i]);
		}
		i++;
	}
	if (!no_nl)
		printf("\n");
	return (0);
}
