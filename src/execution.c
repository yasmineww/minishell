/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/22 16:24:39 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_exp *exp, t_list *list)
{
	int	std_in;
	int	std_out;
	int	inf;
	// int	outf;
	// int	pid;
	int	i;
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
			printf("list->option[i] = %s\n", list->option[i]);
			if (list->option[i] && !ft_strncmp(list->option[i], "<", 1))
			{
				if (list->option[i + 1])
				{
					printf("list->option[i + 1] = %s\n", list->option[i + 1]);
					inf = open(list->option[i + 1], O_RDONLY);
					if (inf == -1)
					{
						perror("open");
						break ;
					}
					dup2(inf, 0);
					close(inf);
					printf("i is %d\n", i);
					i += 2;
					continue ;
				}
			}
			else
				dup2(std_in, inf);
			list = list->next;
			i++;
		}
		// i need to update the option pointer after processing the redirections;
		if (is_builtin(list->option[2]))
			exec_builtin(&exp, list->option);
	}

	return (0);
}
// change prototype t_list instead of char **
int		execute(t_list *list, t_exp *exp)
{
	// char	*tmp;

	// tmp = find_path(envp);
	// if (!tmp)
	// {
	// 	write(2, "env: ", 5);
	// 	if (cmd && *cmd)
	// 		write(2, *cmd, ft_strlen(*cmd));
	// 	write(2, ": No such file or directory\n", 28);
	// }
	// exp->path = ft_split(tmp, ':');
	// if (!exp->path)
	// 	exit(1);
	// free(tmp); // still not working with the paths so the leaks are normal
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
