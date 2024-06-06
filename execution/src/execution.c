/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/06/05 16:51:15 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *get_cmd_path(t_exp *exp, char *cmd)
{
	char *cmdpath;
	char *prefix;
	int i;

	i = 0;
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	while (exp->path[i])
	{
		prefix = ft_strjoin(exp->path[i], "/");
		cmdpath = ft_strjoin(prefix, cmd);
		free(prefix);
		if (!access(cmdpath, X_OK))
			return (cmdpath);
		free(cmdpath);
		i++;
	}
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	return (perror(cmd), exit(0), NULL);

}

void	onecmd_builtin(t_exp *exp, t_list *list)
{
	int std_in = dup(0);
	int std_out = dup(1);
	if (list->option && is_builtin(list->option) && !list->next) // lmochkil hna houa lakant lbuiltin hia lkhra ra tahia next NULL
	{
		// need to refine this function
		exec_builtin(&exp, list->option);
		dup2(std_in, 0);
		close(std_in);
		dup2(std_out, 1);
		close(std_out);
		list->option[0] = NULL;
		if (list->option[1])
			list->option[1] = NULL;
		// bricolage hhhhhhhhh
		return ;
	}
}

int exec(t_exp *exp, t_list *list,  char **envp)
{
	int	fdpipe[2];
	int	std_in;
	int	std_out;
	int *pid;
	int	i;

	if (!list || !list->option)
		return (1);
	std_in = dup(0);
	std_out = dup(1);
	int		count;

	pid = NULL;
	i = 0;
	onecmd_builtin(exp, list);
	count = ft_lstsize(list);
	pid = malloc(sizeof(int) * count);
	if (!pid)
	{
		perror("malloc");
		return (1);
	}
	while (list)
	{
		if (list->next && pipe(fdpipe) == -1)
		{
			perror("pipe");
			exit(1);
		}
		if (list->option && is_builtin(list->option))
		{
			exec_builtin(&exp, list->option);
			dup2(std_in, 0);
			close(std_in);
			dup2(std_out, 1);
			close(std_out);
			return (0);
		}
		pid[i] = fork();
		if (pid[i] < 0)
			perror("fork");
		else if (pid[i] == 0)
		{
			if (i > 0)//check if it's not the first command
			{
				dup2(std_in, 0);
				close(std_in);
			}
			if (list->next)
			{
				close(fdpipe[0]);
				dup2(fdpipe[1], 1);
				close(fdpipe[1]);
			}
			else
			{
				dup2(std_out, 1);
				close(std_out);
			}
			handle_redirs(list);
			if (list->option[0] && is_builtin(list->option))
			{
				exec_builtin(&exp, list->option);
				// dup2(fdpipe[0], 0);
				// close(fdpipe[0]);
				// dup2(fdpipe[1], 1);
				// close(fdpipe[1]);
				exit(0);
			}
			list->option[0] = get_cmd_path(exp, list->option[0]);
			if (list->option[0] && execve(list->option[0], list->option, envp) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else
		{
			if (i > 0)
				close(std_in);
			if (list->next)
			{
				close(fdpipe[1]);
				std_in = fdpipe[0];
			}
		}
		list = list->next;
		i++;
	}
	i = 0;
	while (i < count)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
	dup2(std_in, 0);
	close(std_in);
	dup2(std_out, 1);
	close(std_out);
	return (0);
}

int execute(t_list *list, t_exp *exp, char **envp)
{
	char *tmp;
	tmp = find_path(exp);
	if (!tmp)
	{
		write(2, "env: ", 5);
		if (list->option && list->option[0])
			write(2, list->option[0], ft_strlen(list->option[0]));
		write(2, ": No such file or directory\n", 28);
	}
	exp->path = ft_split(tmp, ':');
	if (!exp->path)
		exit(1);
	// free(tmp);
	exec(exp, list,envp);
	return (0);
}
