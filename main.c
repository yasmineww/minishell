/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:19 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/11 18:44:19 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////DONT TOUCH MAIN 25 LINES PLS///////////

int	setup_prompt(char **input, t_exp *exp)
{
	*input = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler1);
	// printf("exp->status = %d\n", exp->status);
	*input = readline("Minishell$ ");
	if (g_sig == -10)
	{
		// puts("ok");
		exp->status = 1;
	}
	if (!*input || isatty(0) == 0)
	{
		printf("exit\n");
		return (1);
	}
	if (*input && *input[0] != '\0')
		add_history(*input);
	return (0);
}

void	f()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_list	*list;
	t_exp	*exp;

	atexit(f);
	(void)ac;
	(void)av;
	g_sig = 0;
	list = NULL;
	ft_env(&exp, envp);
	if (exp)
		(*exp).status = 0;
	while (1)
	{
		if (setup_prompt(&input, exp) == 1)
			break ;
		if (parsing(input, &list, &exp))
			continue ;
		handle_heredoc(&list, &exp);
		expanding(&list, &exp);
		execute(list, exp, envp);
		list = NULL;
		input = NULL;
	}
}
