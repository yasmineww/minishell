/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:19 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/06/12 16:38:52 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler2(int sig)
{
	(void) sig;
	printf("Quit: 3\n");
}


void	signal_handler1(int sig)
{
	(void) sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	catch_signal(void)
{
	signal(SIGINT, signal_handler1);
	signal(SIGQUIT, signal_handler2);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_list	*list;
	t_exp	*exp;
	struct termios	term;
	(void)ac;
	(void)av;
	list = NULL;
	// madkhlch oldpwd tadir cd
	ft_env(&exp, envp);
	static  char* env_save;
	if (getcwd(NULL, 0))// katkhli leak ig
	{
		env_save = getcwd(NULL, 0);
		exp->pwd = ft_strdup(env_save);
	}
	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGINT, signal_handler1);
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
// Check the PWD in the env so we can update it each time we change the directory if the PWD is not
//found we should create it if Not found Only do an update
//the funtion that gonna handle the pwd Existance and update gonna Return the index of the PWD in the env
// if the PWD is not found it would Rtrunr -1
// if the return value is -1 we should create the PWD in the env and add it with the addback function
// if the return value is not -1 we should update the index of PWD in the env
