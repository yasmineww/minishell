/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:19 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/23 23:41:26 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////DONT TOUCH MAIN 25 LINES PLS///////////

int	setup_prompt(t_mini *mini, char **input)
{
	*input = NULL;
	// exp->ambiguous = 0;
	// exp->expanded = 0;
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	*input = readline("Minishell$ ");
	if (g_sig == 4)
		mini->status = 1;
	if (!*input || isatty(0) == 0)
	{
		printf("exit\n");
		ft_free(mini->exp->path);
		free_env(mini->exp, 1);
		free(mini->exp->pwd);
		exit (mini->status);
	}
	if (*input && *input[0] != '\0')
		add_history(*input);
	return (0);
}

void	set_pwd(t_mini *mini)
{
	static char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		mini->exp->pwd = ft_strdup(cwd);
		free(cwd);
	}
	mini->status = 0;
}

void	free_list(t_list *list)
{
	t_list	*temp;
	int		i;

	while (list)
	{
		temp = list;
		free(temp->cmd);
		temp->cmd = NULL;
		i = 0;
		while (temp->option[i])
		{
			free(temp->option[i]);
			temp->option[i] = NULL;
			i++;
		}
		free(temp->option);
		temp->option = NULL;
		list = temp->next;
		free(temp);
	}
}

void	f()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_list	*list;
	// t_exp	*exp;
	t_mini	mini;

	// atexit(f);
	(void)ac;
	(void)av;
	g_sig = 0;
	list = NULL;
	// ft_env(&exp, envp);
	ft_env(&mini.exp, envp);
	set_pwd(&mini);
	while (1)
	{
		setup_prompt(&mini, &input);
		if (parsing(&mini, input))
			continue ;
		handle_heredoc(&mini);
		// expanding(&list, &exp, NULL);
		// execute(list, &exp, envp);
		// free_list(list);
		// list = NULL;
	}
}
