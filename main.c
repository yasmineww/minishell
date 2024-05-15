/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/15 22:03:31 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    main ()
{
	char	*input;
    t_list	*list;

    while (1)
    {
		input = readline("Minishell$ ");
		if(!input)
			return (0);
		add_history(input);
		if (quotes_syntax_error(input) || syntax_error(input))
		{
			error_message(input);
			continue ;
		}
		store_cmd(input, &list);
		while (list)
		{
			printf("node : %s\n", *list->command);
			list = list->next;
		}
		list = NULL;
		free(input);
		input = NULL;
    }
}
