/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/24 22:22:28 by mbenchel         ###   ########.fr       */
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
	return (NULL);
}

int exec(t_exp *exp, t_list *list)
{
	int pid;
	int i;
	int fdpipe[2];
	int std_in;
	int std_out;
	if (!list || !list->option)
		return (1);
	std_in = dup(0);
	std_out = dup(1);
	while (list)
	{
		handle_redir_in(list);
		if (list->infile)
		{
			dup2(list->infile, 0);
			close(list->infile);
		}
		handle_redir_out(list);
		if (list->outfile)
		{
			dup2(list->outfile, 1);
			close(list->outfile);
		}
		handle_append(list);
		if (list->outfile)
		{
			dup2(list->outfile, 1);
			close(list->outfile);
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
		i = 0;
		if (list->next && pipe(fdpipe) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid < 0)
			perror("fork");
		else if (pid == 0)
		{
			if (list->next)
			{
				close(fdpipe[0]);
				dup2(fdpipe[1], 1);
				close(fdpipe[1]);
			}
			list->option[0] = get_cmd_path(exp, list->option[0]);
			if (list->option[0] && execve(list->option[0], list->option, exp->path) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else
		{
			if (list->next)
			{
				close(fdpipe[1]);
				dup2(fdpipe[0], 0);
				close(fdpipe[0]);
			}
			waitpid(-1, NULL, 0);
		}
		list = list->next;
	}
	dup2(std_in, 0);
	close(std_in);
	dup2(std_out, 1);
	close(std_out);
	return (0);
}

int execute(t_list *list, t_exp *exp, char **envp)
{
	char *tmp;

	tmp = find_path(envp);
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
	free(tmp);
	exec(exp, list);
	return (0);
}
