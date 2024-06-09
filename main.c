/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/06/09 23:21:19 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_list	*list;
	t_exp	*exp;
	struct termios	term;
		(void)ac;
	(void)av;
	list = NULL;
	ft_env(&exp, envp);
	while (1)
	{
		// rl_catch_signals = 0;
		// \n
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		// SIGINT and SIGQUIT
		// print QUIT \n
		// SIG_DFL;
		input = readline("Minishell$ ");
		if (!input || isatty(0) == 0)
			break;
		add_history(input);
		parsing(input, &list);
		handle_heredoc(&list, &exp);
		expanding(&list, &exp);
		tcgetattr(0, &term);
		execute(list ,exp, envp);
		tcsetattr(0, 0, &term);
		list = NULL;
		// free(input);
		input = NULL;
	}
}
