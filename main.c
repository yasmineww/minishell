/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/17 15:20:19 by ymakhlou         ###   ########.fr       */
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
	while (exp)
	{
		printf("%s=%s\n", exp->key, exp->value);
		exp = exp->next;
	}
	while (1)
	{
		input = readline("Minishell$ ");
		if (!input)
			return (0);
		add_history(input);
		if (quotes_syntax_error(input) || syntax_error(input))
		{
			error_message(input);
			continue ;
		}
		input = add_space(input);
		store_cmd(input, &list);
		split_cmd(&list);
		// while (list)
		// {
		// 	printf("node.cmd : %s\n", list->cmd);
		// 	int i = -1;
		// 	while (list->command[++i])
		// 		printf("node.command[%i] : %s\n",i,list->command[i]);
		// 	list = list->next;
		// 	puts("--------------------------------------");
		// }
		list = NULL;
		free(input);
		input = NULL;
	}
}
