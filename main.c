/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/09 18:27:00 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    syntax_error(char *ptr)
{
    int     count;
	int		i;

	i = 0;
	count = count_arg(ptr);
	if (count == 0)
		return ;
	else if (count == 1)
	{
        if (special_char(ptr))
			error_message();
	}
	else if (count > 1)
	{
		while (check_space(&ptr[i]))
			i++;
		if (ptr[i] == '|')
			error_message();
		while (ptr[i] != '\0')
			i++;
		while (check_space(&ptr[i - 1]))
			i--;
		if (special_char(&ptr[i - 1]))
			error_message();
		i = 0;
		while (ptr[i] != '\0')
		{
			if (special_char(&ptr[i]))
			{
				i++;
				while (check_space(&ptr[i]))
					i++;
				if (special_char(&ptr[i]))
					error_message();
			}
			i++;
		}
	}
}

int main ()
{
    char    *input = NULL;
    char    *ptr;

    while(1)
    {
        input = readline("Minishell$ ");
        add_history(input);
        ptr = input;
        syntax_error(input);
    }
}
