/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:37 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/23 23:49:08 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a struct of the commands
// start working on built-ins

void f()
{
	system("leaks minishell");
}

int main(int ac,char **av ,char **envp)
{
	// atexit(f);
	t_list	*list = NULL;
	t_list	*head = NULL;
	t_list	*cur;
	t_exp	*exp;
	(void)ac;
	(void)av;
	char *tmp;
	int i = 0;
	ft_env(&exp, envp);
	while (1)
	{
		i = 0;
		tmp = readline("bash-3.2$ ");
		if (tmp)
		{
			if (tmp[0] == '\0')
				continue;
		}
		else
			exit(0);
		add_history(tmp);
		list = malloc(sizeof(t_list));
		if (!list)
		{
			free(tmp);
			exit(1);
		}
		list->option = ft_split(tmp, ' ');
		list->next = NULL;
		if (!head)
			head = list;
		else
		{
			cur = head;
			while (cur->next)
				cur = cur->next;
			cur->next = list;
		}
		i = 0;
		while(list->option[i])
		{
			if (list->option[i][0] == '|')
			{
				list->option[i] = NULL;
				list->next = malloc(sizeof(t_list));
				if (!list->next)
				{
					free(tmp);
					exit(1);
				}
				list->next->option = &list->option[i + 1];
				list->next->next = NULL;
				list = list->next;
				i = 0;
			}
			else
				i++;
		}
		list = head;
		execute(list ,exp, envp);
		head = NULL;
	}
	return (0);
}

// int main() {
//     int original_stdout = dup(1); // Save the original stdout file descriptor

//     // Execute the command "ls > outfile"
//     FILE *outfile = fopen("outfile", "w");
//     dup2(fileno(outfile), 1);
//     fclose(outfile);
//     system("ls");

//     // Restore the original stdout
//     // dup2(original_stdout, 1);

//     // Display a new prompt
//     printf("\nReady to execute another command...\n");
// 	printf("here");
//     // Execute the command "ls" without redirection
//     system("ls");

//     return 0;
// }
