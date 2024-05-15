/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/15 19:42:11 by ymakhlou         ###   ########.fr       */
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
		add_history(input);
		if (quotes_syntax_error(input) || syntax_error(input))
		{
			error_message(input);
			continue ;
		}
		store_cmd(input, &list);
		list = NULL;
		free(input);
		input = NULL;
    }
}

	// while (list)
	// {
	// 	printf("%s\n", *list->command);
	// 	list = list->next;
	// }