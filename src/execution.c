/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/21 01:49:32 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_exp *exp, t_list *list)
{
	int	std_in;
	int	std_out;
	int	inf;
	if (is_builtin(list->option))
		exec_builtin(&exp, list->option);
	else
	{
		std_in = dup(0);
		std_out = dup(1);
		if (list->infile)
		{
			inf = open(list->option[1], O_RDONLY);
			dup2(inf, 0);
			close(inf);
		}
		else
			dup2(std_in, inf);
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
