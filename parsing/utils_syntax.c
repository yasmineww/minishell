/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:57:59 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/24 16:18:05 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	error_message(char *input)
{
	write(2, "Minishell: syntax error\n", 25);
	free(input);
	input = NULL;
	return (1);
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
	if (*ptr == '|' || *ptr == '<' || *ptr == '>'
		|| (ft_strcmp(ptr, "<<") == 0) || (ft_strcmp(ptr, ">>") == 0))
		return (1);
	return (0);
}

int	check_space(char *ptr)
{
	if ((*ptr >= 9 && *ptr <= 13) || *ptr == 32)
		return (1);
	return (0);
}
