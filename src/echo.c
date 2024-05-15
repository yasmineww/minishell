/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:27:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/15 23:53:23 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo_print(char **cmd, int i, int no_nl)
{
	while (cmd[i])
	{
		if (!(cmd[i][0] == '-' && cmd[i][1] == 'n'))
		{
			printf("%s", cmd[i]);
			i++;
			if (cmd[i])
				printf(" ");
		}
		else
			i++;
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
		while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
		{
			no_nl = 1;
			i++;
			printf("i = %d\n", i);
		}
		j = 0;
		while (cmd[i] && cmd[i][j] && cmd[i][0] == '-' && cmd[i][1] == 'n')
		{
			puts("here");
			no_nl = 1;
			j++;
		}
		j = 2;
		if (cmd[i][j])
		{
			puts("here");
			printf("cmd[i][j] = %c\n", cmd[i][j]);
			no_nl = 0;
			break ;
		}
		i++;
	}
	echo_print(cmd, i, no_nl);
	return (0);
}
// int	ft_echo(char **cmd)
// {
// 	int	params;
// 	int	i;
// 	int	no_nl;
// 	int	j;

// 	i = 1;
// 	no_nl = 0;
// 	j = 1;
// 	params = countparams(cmd);
// 	if (params > 1 && ft_strncmp(cmd[1], "-n", 2) == 0)
// 		no_nl = 1;
// 	while (i < params)
// 	{
// 		if (cmd[i] && cmd[i][0] == '-')
// 		{
// 			while (cmd[i][j])
// 			{
// 				if (cmd[i][j] != 'n')
// 				{
// 					no_nl = 0;
// 					break;
// 				}
// 				j++;
// 			}
// 			if (!cmd[i][j] && cmd[i][j - 1] == 'n')
// 			{
// 				if (i + 1 < params && cmd[i + 1] && cmd[i + 1][0] != '-')
// 					no_nl = 1;
// 			}
// 		}
// 		else
// 		{
// 			if (i == params - 1)
// 				printf("%s", cmd[i]);
// 			else
// 				printf("%s ", cmd[i]);
// 		}
// 		i++;
// 	}
// 	if (!no_nl)
// 		printf("\n");
// 	return (0);
// }
