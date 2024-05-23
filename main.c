/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/23 13:04:23 by ymakhlou         ###   ########.fr       */
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
	// while (exp)
	// {
	// 	printf("%s=%s\n", exp->key, exp->value);
	// 	exp = exp->next;
	// }
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input)
			return (0);
		add_history(input);
		parsing(input, &list);
		expanding(&list, &exp);
		handle_heredoc(&list, &exp);
		t_list *tmp = list;
		while (tmp)
		{
			printf("node.cmd : %s\n", tmp->cmd);
			int i = -1;
			while (tmp->option[++i])
				printf("node.option[%i] : %s and node.fd[%i] : %d\n",i,tmp->option[i], i, tmp->heredoc);
			tmp = tmp->next;
			puts("--------------------------------------");
		}
		list = NULL;
		// free(input);
		input = NULL;
	}
}
