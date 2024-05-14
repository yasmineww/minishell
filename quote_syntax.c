/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:46:52 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/14 22:03:42 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multiply_minus(char *input, char c)
{
	// puts("ok");
	while (*input != c)
		input++;
	input++;
	while (*input != c)
	{
		// printf("input: %c\n", *input);
		*input *= -1;
		input++;
	}
	return 1;
}

int	count_quote(char *input, char c)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (*input == c)
			count++;
		input++;
	}
	return (count);
}

int handle_quotes(char **command) 
{
	char	*str;
	char	quote;

	str = *command;
	while (*str)
	{
		if (*str == '\'' || *str == '"') 
		{
			quote = *str;
			// printf("str: %c\n", *str);
			if (count_quote(*command, quote) % 2 == 0)
			{
				multiply_minus(str, quote);
				// break ;
			}
			else if (count_quote(*command, quote) % 2 == 1)
				return 1;
		}
		str++;
	}
	return 0;
}

int	quotes_syntax_error(char *input)
{
	while (*input)
	{
		if (handle_quotes(&input))
			return 1;
		else
			return 0;
		input++;
	}
	return 0;
}
