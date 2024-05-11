/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:53:20 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/11 22:44:37 by mbenchel         ###   ########.fr       */
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
		else if ((i == j) && ptr[i] == '>') // handle >>>
		{
			if (special_char(&ptr[i + 1]))
				return (1);
		}
		else if ((i != j) && (special_char(&ptr[i]))) // compare i & j to check for white spaces
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
		else if ((i == j) && ptr[i] == '<') // handle <<<
		{
			if (special_char(&ptr[i + 1]))
				return (1);
		}
		else if ((i != j) && (special_char(&ptr[i]))) // compare i & j to check for white spaces
			return (1);
	}
	if(helper(&ptr[i]))
		return (1);
	return (0);
}

void	two_specials(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == '|')//case 1 pipes : ||
		{
			i++;
			while (check_space(&ptr[i]))
				i++;
			if (ptr[i] == '|')
				if(error_message())
					return ;
		}
		else if (delimiter(&ptr[i]))//case 2 starts with < or >
		{
			if(error_message())
				return ;
		}
		i++;
	}
}

void	special_last(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != '\0')
		i++;
	while (check_space(&ptr[i - 1]))
		i--;
	if (special_char(&ptr[i - 1]))
		if(error_message())
			return ;
}

void    syntax_error(char *ptr)
{
    int     count;
	int		i;

	i = 0;
	count = count_arg(ptr);
	if (count == 0) // case 1 : no args
		return ;
	else if (count == 1) // case 2 : one arg
	{
        if (special_char(ptr))
			if(error_message())
				return ;
	}
	else if (count > 1) // case 3 : multiple args
	{
		while (check_space(&ptr[i]))
			i++;
		if (ptr[i] == '|') // case 3.1 : pipe first
			if(error_message())
				return ;
		special_last(ptr); // case 3.2 : special char last
		two_specials(ptr); // case 3.3 : two specials in a row
	}
}
