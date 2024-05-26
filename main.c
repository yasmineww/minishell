/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/26 23:24:18 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_list	*list;
	t_exp	*exp;

	(void)ac;
	(void)av;
	ft_env(&exp, envp);
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input)
			break;
		add_history(input);
		parsing(input, &list);
		handle_heredoc(&list, &exp);
		expanding(&list, &exp);
		execute(list ,exp, envp);
		list = NULL;
		// free(input);
		input = NULL;
	}
}
