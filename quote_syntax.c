/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:46:52 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/16 15:15:06 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cases(char *ptr, int i)
{
	if (ptr[i] == '|') // case 3.1 : pipe first
		return (1);
	if(special_last(ptr)) // case 3.2 : special char last
		return (1);
	if (two_specials(ptr)) // case 3.3 : two specials in a row
		return (1);
	return (0);
}

int	count_quote(char *input)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] && input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				input[i++] *= -1;
		}
		if (input[i] && input[i] == '\"')
		{
			i++;
			while (input[i] && input[i] != '\"')
				input[i++] *= -1;
		}
	}
	i = -1;
	while (input[++i])
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
			count++;
	return (count);
}

int	quotes_syntax_error(char *input)
{
	int	num;

	num = count_quote(input);
	if (num % 2 != 0)
		return (1);
	return (0);
}
