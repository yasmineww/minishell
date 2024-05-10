/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:56:04 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/10 12:17:36 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg(char *str)
{
	int	count;


	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (!check_space(str))
		{
			count++;
			while (*str && !check_space(str))
				str++;
		}
		else
			str++;
	}
	return (count);
}

void    error_message()
{
    write(2, "Minishell: syntax error\n", 25);
	return ;
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	special_char(char *ptr)
{
	if (*ptr == '|' || *ptr == '<' || *ptr == '>' || (ft_strcmp(ptr, "<<") == 0) || (ft_strcmp(ptr, ">>") == 0))
	 	return (1);
	return (0);
}

int	check_space(char *ptr)
{
	if ((*ptr >= 9 && *ptr <= 13) || *ptr == 32)
		return (1);
	return (0);
}
