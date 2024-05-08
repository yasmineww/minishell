/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:37 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/08 17:51:21 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// create a struct of the commands
// start working on built-ins


int	exec(t_env *env, char **envp, char **cmd)
{
	(void)envp;
	is_builtin(env, cmd);
	system("ls");
	return (0);
}

int		execute(char **envp, char **cmd, t_env *env)
{
	char	*tmp;

	tmp = find_envp(envp);
	if (!tmp)
	{
		write(2, "env: ", 5);
		if (cmd && *cmd)
			write(2, *cmd, ft_strlen(*cmd));
		write(2, ": No such file or directory\n", 28);
	}
	env->path = ft_split(tmp, ':');
	if (!env->path)
		exit(1);
	free(tmp);
	exec(env, envp, cmd);
	return (0);
}

int main(int ac,char **av ,char **envp)
{
	t_env	env;
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
		execute(envp, res ,&env);
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
