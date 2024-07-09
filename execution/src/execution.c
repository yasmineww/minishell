/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/09 22:40:38 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cmd_path(t_exp *exp, char *cmd)
{
	char	*cmdpath;
	char	*prefix;
	int		i;

	if (!cmd)
		exit(1);
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
	return (perror(cmd), exit(1), NULL);
}

void	check_value_export(t_list *list)
{
	int		i;
	int		j;
	char	**s;

	i = 0;
	j = 0;
	while (list->option[i])
	{
		if (ft_strlen(list->option[i]) > 0)
			j++;
		i++;
	}
	s = malloc(sizeof(char *) * (j + 1));
	if (!s)
		exit(1);
	i = 0;
	j = 0;
	while (list->option[i])
	{
		if (ft_strlen(list->option[i]) > 0)
		{
			s[j] = list->option[i];
			j++;
		}
		i++;
	}
	s[j] = NULL;
	list->option = s;
}

void	onecmd_builtin(t_exp *exp, t_list *list)
{
	int	std_in;
	int	std_out;

	std_in = dup(0);
	std_out = dup(1);
	if (!list || !list->option || list->next)
		return ;
	if (is_builtin(list->option))
	{
		handle_redirs(list);
		exec_builtin(&exp, list->option);
		list->option[0] = NULL;
		if (list->option[1])
			list->option[1] = NULL;
	}
	close(std_in);
	close(std_out);
}

int	exec(t_exp *exp, t_list *list, char **envp)
{
	int	fdpipe[2];
	int	std_in;
	int	std_out;
	int	*pid;
	int	i;
	int	count;
	static int	status;
	int		exitcode;

	if (!list || !list->option)
		return (1);
	std_in = dup(0);
	std_out = dup(1);
	pid = NULL;
	i = 0;
	signal(SIGQUIT, signal_handler2);
	check_value_export(list);
	count = ft_lstsize(list);
	if (count == 1)
		onecmd_builtin(exp, list);
	pid = malloc(sizeof(int) * count);
	if (!pid)
		return (1);
	while (list)
	{
		if (list->next && pipe(fdpipe) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid[i] = fork();
		// catch signal command
		if (pid[i] < 0)
			perror("fork");
		else if (pid[i] == 0)
		{
			if (i > 0)
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
			if (list->option[0] && is_builtin(list->option))
			{
				handle_redirs(list);
				exec_builtin(&exp, list->option);
				dup2(fdpipe[0], 0);
				close(fdpipe[0]);
				dup2(fdpipe[1], 1);
				close(fdpipe[1]);
				exit(0);
			}
			else
				handle_redirs(list);
			list->option[0] = get_cmd_path(exp, list->option[0]);
			if (list->option[0]
				&& execve(list->option[0], list->option, envp) == -1)
			{
				perror("execve");
				exit(127);
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
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			exitcode = WEXITSTATUS(status);
		i++;
	}
	free(pid);
	dup2(std_in, 0);
	close(std_in);
	dup2(std_out, 1);
	close(std_out);
	return (0);
}

int	execute(t_list *list, t_exp *exp, char **envp)
{
	char			*tmp;
	struct termios	term;

	tcgetattr(0, &term);
	if (g_sig == 1)
	{
		g_sig = 0;
		return (0);
	}
	tmp = find_path(exp);
	exp->path = ft_split(tmp, ':');
	if (!exp->path)
		exit(1);
	// free(tmp);
	exec(exp, list, envp);
	tcsetattr(0, 0, &term);
	return (0);
}
