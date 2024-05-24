/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:27:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/24 16:14:20 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void echo_print(char **cmd, int i, int no_nl)
{
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
			printf(" ");
	}
	if (!no_nl)
		printf("\n");
}

int	ft_echo(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	int	no_nl = 0;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
		{
			j = 2;
			while (cmd[i][j] && cmd[i][j] == 'n')
				j++;
			if (cmd[i][j])
			{
				no_nl = 0;
				break ;
			}
			no_nl = 1;
		}
		else
			break ;
		i++;
	}
	echo_print(cmd, i, no_nl);
	return (0);
}
