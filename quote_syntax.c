/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:46:52 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/15 20:09:46 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quote(char **input)
{
	int	count;
	int i;
	
	count = 0;
	 i = -1;
	while (input[0][++i])
	{
		if (input[0][i] && input[0][i] == '\'')
		{
			i++;
			while (input[0][i] && input[0][i] != '\'')
				input[0][i++] *= -1;
		}
		if (input[0][i] && input[0][i] == '\"')
		{
			i++;
			while (input[0][i] && input[0][i] != '\"')
				input[0][i++] *= -1;
		}
	}
	i = -1;
	while (input[0][++i])
		if(input[0][i] && (input[0][i] == '\'' || input[0][i] == '\"'))
			count++;
	return (count);
}

int handle_quotes(char **command) 
{
	char	*str;

	str = *command;
	int num = count_quote(command);
	if(num % 2 != 0)
		return (1);
	return 0;
}

int	quotes_syntax_error(char *input)
{
	if (handle_quotes(&input))
		return 1;
	return 0;
}
