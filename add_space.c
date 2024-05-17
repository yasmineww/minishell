/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:13:07 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/17 11:44:45 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_case(char **input, char **new, int i)
{
	(*new)[i++] = ' ';
	(*new)[i++] = **input;
	if ((**input == '>' && *(*input+1) == '>')
		|| (**input == '<' && *(*input+1) == '<'))
	{
		(*new)[i++] = **input;
		(*input)++;
	}
	if (!(*(*input+1) == '>' || *(*input+1) == '<'))
		(*new)[i++] = ' ';
	return (i);
}

int	ft_strlen(char	*av)
{
	int	count;

	count = 0;
	while (*av)
	{
		count++;
		av++;
	}
	return (count);
}

char	*add_space(char *input)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(input) * 2 + 1);
	if (!new)
		return (NULL);
	while (*input)
	{
		if (special_char(input))
		{
			i = special_case(&input, &new, i);
		}
		else
			new[i++] = *input;
		input++;
	}
	new[i] = '\0';
	printf("added :%s\n", new);
	return (new);
}