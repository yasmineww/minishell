/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/06/07 01:29:05 by ymakhlou         ###   ########.fr       */
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
	list = NULL;
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
		puts("ok66");
		list = NULL;
		// free(input);
		input = NULL;
	}
}
