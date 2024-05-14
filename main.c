/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/14 22:06:58 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    main ()
{
    char	*input;
    t_list	*list;
	int		tr;	

    while (1)
    {
		input = readline("Minishell$ ");
		puts("ok1");
		add_history(input);
		if (quotes_syntax_error(input))
			tr = 1;
		if (syntax_error(input) || tr == 1)
		{
			puts("ok2");
			error_message();
			tr = 0;
		}
		puts("ok3");
		store_cmd(input, &list);
		list = NULL;
    }
}

		// while (list)
		// {
		// 	printf("%s\n", *list->command);
		// 	list = list->next;
		// }