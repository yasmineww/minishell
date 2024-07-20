/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:19 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/20 16:22:34 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////DONT TOUCH MAIN 25 LINES PLS///////////

int	setup_prompt(char **input, t_exp *exp)
{
	int	stat;

	*input = NULL;
	exp->ambiguous = 0;
	exp->expanded = 0;
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	*input = readline("Minishell$ ");
	if (g_sig == 4)
		exp->status = 1;
	if (!*input || isatty(0) == 0)
	{
		stat = exp->status;
		printf("exit\n");
		ft_free(exp->path);
		free_env(exp);
		free(exp->pwd);
		exit (stat);
	}
	if (*input && *input[0] != '\0')
		add_history(*input);
	return (0);
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
	if (exp)
		(*exp).status = 0;
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
	t_exp	*exp;
	int		pwd_oldpwd;

	atexit(f);
	pwd_oldpwd = 0;
	(void)ac;
	(void)av;
	g_sig = 0;
	list = NULL;
	ft_env(&exp, envp);
	set_pwd(exp);
	while (1)
	{
		if (setup_prompt(&input, exp))
			break ;
		if (parsing(input, &list, &exp))
			continue ;
		handle_heredoc(&list, &exp);
		expanding(&list, &exp);
		execute(list, &exp, envp);
		free_list(list);
		list = NULL;
	}
}
