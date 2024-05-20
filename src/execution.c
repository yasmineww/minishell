/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:47:35 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/20 21:56:48 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_exp *exp, t_list *list)
{
	is_builtin(&exp, list->option);

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
