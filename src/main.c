/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:37 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/22 20:19:13 by mbenchel         ###   ########.fr       */
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
		if (!tmp)
			break;
		add_history(tmp);
		list = malloc(sizeof(t_list));
		if (!list)
		{
			free(tmp);
			exit(1);
		}
		list->option = ft_split(tmp, ' ');
		if (!list->option)
		{
			free(list);
			free(tmp);
			exit(1);
		}
		execute(list ,exp, envp);
		free(tmp);
		//declare input struct and change execute prototype to accept list
	}
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
