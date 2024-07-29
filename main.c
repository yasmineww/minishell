/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:19 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/29 12:00:05 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_prompt(t_mini *mini, char **input)
{
	*input = NULL;
	mini->list = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	*input = readline("Minishell$ ");
	if (g_sig == 4)
		mini->status = 1;
	if (!*input || isatty(0) == 0)
	{
		printf("exit\n");
		ft_free(mini->path);
		free_env(mini->exp);
		free(mini->pwd);
		exit (mini->status);
	}
	if (*input && *input[0] != '\0')
		add_history(*input);
	return (0);
}

void	set_pwd(t_mini *mini)
{
	static char	*cwd;

	mini->path_unset = 0;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		mini->pwd = ft_strdup(cwd);
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
		if (temp->infile)
			close(temp->infile);
		free(temp->option);
		temp->option = NULL;
		list = temp->next;
		free(temp);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_mini	mini;

	(void)ac;
	(void)av;
	g_sig = 0;
	ft_env(&mini.exp, envp);
	mini.path = NULL;
	set_pwd(&mini);
	while (1)
	{
		setup_prompt(&mini, &input);
		if (parsing(&mini, input))
			continue ;
		if (handle_heredoc(&mini, NULL))
		{
			free_list(mini.list);
			continue ;
		}
		expanding(&mini, 0, 0, NULL);
		execute(&mini);
		free_list(mini.list);
		mini.list = NULL;
	}
}
