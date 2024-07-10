/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:53:20 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/10 12:21:45 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	helper(char *ptr)
{
	int	i;
	int	j;

	i = 0;
	if (*ptr == '>')
	{
		i++;
		j = i;
		while (check_space(&ptr[i]))
			i++;
		if ((i == j) && (ptr[i] == '<' || ptr[i] == '|'))
			return (1);
		else if ((i == j) && ptr[i] == '>')
		{
			if (special_char(&ptr[i + 1]))
				return (1);
		}
		else if ((i != j) && (special_char(&ptr[i])))
			return (1);
	}
	return (0);
}

int	delimiter(char *ptr)
{
	int	i;
	int	j;

	i = 0;
	if (*ptr == '<')
	{
		i++;
		j = i;
		while (check_space(&ptr[i]))
			i++;
		if ((i == j) && (ptr[i] == '>' || ptr[i] == '|'))
			return (1);
		else if ((i == j) && ptr[i] == '<')
		{
			if (special_char(&ptr[i + 1]))
				return (1);
		}
		else if ((i != j) && (special_char(&ptr[i])))
			return (1);
	}
	if (helper(&ptr[i]))
		return (1);
	return (0);
}

int	two_specials(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == '|')
		{
			i++;
			while (check_space(&ptr[i]))
				i++;
			if (ptr[i] == '|')
				return (1);
		}
		else if (delimiter(&ptr[i]))
			return (1);
		i++;
	}
	return (0);
}

int	special_last(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != '\0')
		i++;
	while (check_space(&ptr[i - 1]))
		i--;
	if (special_char(&ptr[i - 1]))
		return (1);
	return (0);
}
