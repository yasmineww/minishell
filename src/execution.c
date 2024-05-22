/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/22 20:47:12 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(t_exp *exp, char *cmd)
{
	char	*cmdpath;
	char	*prefix;
	int		i;

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
int	exec(t_exp *exp, t_list *list)
{
	int	std_in;
	int	std_out;
	int	inf;
	int	outf;
	int	pid;
	int	i;
	int	j;
//		outf = open(data.output, O_RDWR | O_CREAT | O_TRUNC, 0644);

	i = 0;
	if (is_builtin(list->option))
		exec_builtin(&exp, list->option);
	else
	{
		std_in = dup(0);
		std_out = dup(1);
		while (list != NULL)
		{
			i = 0;
			while (list->option && list->option[i])
			{
				if (!ft_strncmp(list->option[i], "<", 1))
				{
					if (list->option[i + 1])
					{
						inf = open(list->option[i + 1], O_RDONLY);
						if (inf == -1)
						{
							perror("open");
							break ;
						}
						j = i;
						while (list->option[j])
						{
							list->option[j] = list->option[j + 2];
							j++;
						}
						continue ;
					}
					else
						inf = dup(std_in);
				}
					i++;
			}
			if (is_builtin(list->option))
				exec_builtin(&exp, list->option);
			else
			{
				pid = fork();
				if (pid < 0)
				{
					perror("fork");
					exit(1);
				}
				else if (pid == 0)
				{
					list->option[0] = get_cmd_path(exp, list->option[0]);
					if (execve(list->option[0], list->option, exp->path) == -1)
					{
					// dup input and output
						perror("execve");
						exit(1);
					}
				}
				else
					waitpid(-1, NULL, 0);
			}
			list = list->next;
		}
	}
	return (0);

}
// change prototype t_list instead of char **
int		execute(t_list *list, t_exp *exp, char **envp)
{
	char	*tmp;

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
	free(tmp); // still not working with the paths so the leaks are normal
	exec(exp, list);
	int i = 0;
	while (list->option[i])
	{
		free(list->option[i]);
		i++;
	}
	free(list->option);
	return (0);
}
