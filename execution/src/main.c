/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:37 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/11 22:47:12 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// create a struct of the commands
// start working on built-ins

void f()
{
	system("leaks minishell");
}

int	exec(t_exp *exp, char **envp, char **cmd)
{
	is_builtin(&exp, cmd, envp);
	return (0);
}

int		execute(char **envp, char **cmd, t_exp *exp)
{
	char	*tmp;

	tmp = find_path(envp);
	if (!tmp)
	{
		write(2, "env: ", 5);
		if (cmd && *cmd)
			write(2, *cmd, ft_strlen(*cmd));
		write(2, ": No such file or directory\n", 28);
	}
	exp->path = ft_split(tmp, ':');
	if (!exp->path)
		exit(1);
	free(tmp);
	exec(exp, envp, cmd);
	int i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	return (0);
}

int main(int ac,char **av ,char **envp)
{
	atexit(f);
	t_exp	exp;
	(void)ac;
	(void)av;
	char **res = NULL;
	char *tmp;
	int i = 0;
	while (1)
	{
		i = 0;
		tmp = readline("minishell >>");
		res = ft_split(tmp, ' ');
		if (!res)
			exit(1);
		execute(envp, res ,&exp);
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
