/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:19 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/10 12:18:46 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////DONT TOUCH MAIN 25 LINES PLS///////////

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
		rl_catch_signals = 0;
		signal(SIGINT, signal_handler1);
		input = readline("Minishell$ ");
		if (!input || isatty(0) == 0)
			break ;
		add_history(input);
		parsing(input, &list);
		handle_heredoc(&list, &exp);
		expanding(&list, &exp);
		execute(list, exp, envp);
		list = NULL;
		input = NULL;
	}
}
//oldpwd tadir cd 3ad dkhlo (optional)
// Check the PWD in the env so we can update it each time we change the directory if the PWD is not
//found we should create it if Not found Only do an update
//the funtion that gonna handle the pwd Existance and update gonna Return the index of the PWD in the env
// if the PWD is not found it would Rtrunr -1
// if the return value is -1 we should create the PWD in the env and add it with the addback function
// if the return value is not -1 we should update the index of PWD in the env
