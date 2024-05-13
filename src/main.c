/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:37 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/13 11:01:38 by mbenchel         ###   ########.fr       */
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
	t_exp	*exp;
	(void)ac;
	(void)av;
	char **res = NULL;
	char *tmp;
	int i = 0;
	while (1)
	{
		i = 0;
		tmp = readline("bash-3.2$ ");
		res = ft_split(tmp, ' ');
		if (!res)
			exit(1);
		ft_env(&exp, envp, 0);
		execute(envp, res ,exp);
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
