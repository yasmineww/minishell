/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:27:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/17 11:01:09 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	function_skipp_it(char *string)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (check_space(&string[index]) && !check_space(&string[index + 1]))
			write(1, " ", 1);
		else if (!check_space(&string[index]))
			write(1, &string[index], 1);
		index++;
	}
}

void	echo_print(char **cmd, int i, int no_nl, t_exp *exp)
{
	int	index;

	index = 0;
	while (cmd[i])
	{
		index = 0;
		if (exp->expanded == 1)
		{
			while (cmd[i][index] == ' ' || cmd[i][index] == '\t')
				index++;
			function_skipp_it(&cmd[i][index]);
		}
		else
		{
			while (cmd[i][index])
			{
				write(1, &cmd[i][index], 1);
				index++;
			}
		}
		i++;
	}
	if (!no_nl)
		write(1, "\n", 1);
}

int	ft_echo_helper(char **cmd, int *no_nl)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
		{
			j = 2;
			while (cmd[i][j] && cmd[i][j] == 'n')
				j++;
			if (cmd[i][j])
				break ;
			*no_nl = 1;
		}
		else
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(char **cmd, t_exp *exp)
{
	int	no_nl;
	int	i;

	no_nl = 0;
	i = ft_echo_helper(cmd, &no_nl);
	echo_print(cmd, i, no_nl, exp);
	exp->status = 0;
	return (0);
}
