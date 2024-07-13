/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:19 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/13 09:54:14 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////DONT TOUCH MAIN 25 LINES PLS///////////

int	setup_prompt(char **input, t_exp *exp)
{
	*input = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	*input = readline("Minishell$ ");
	if (g_sig == 4)
		exp->status = 1;
	if (!*input || isatty(0) == 0)
	{
		printf("exit\n");
		free_env(exp);
		free(exp->pwd);
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

void	set_pwd(t_exp *exp)
{
	static char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		exp->pwd = ft_strdup(cwd);
		free(cwd);
	}
}

void	free_list(t_list *list)
{
	t_list	*temp;
	int 	i;

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
	set_pwd(exp);
	if (exp)
		(*exp).status = 0;
	while (1)
	{
		if (setup_prompt(&input, exp) == 1)
		{
			free(input);///added this
			break ;
		}
		if (parsing(input, &list, &exp))
			continue ;
		handle_heredoc(&list, &exp);
		expanding(&list, &exp);
		execute(list, exp, envp);
		input = NULL;
		free_list(list);
		int i = 0;
		t_list *temp = list;
		while (temp)
		{
			free(temp->cmd);
			temp->cmd = NULL;
			i = 0;
			while (list->option[i])
			{
				free(list->option[i]);
				list->option[i] = NULL;
				i++;
			}
			free(list->option);
			list->option = NULL;
			list = temp->next;
			free(temp);
			temp = list;
		}
		list = NULL;
	}
}
