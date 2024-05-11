/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:36:55 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/11 22:47:28 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void errorlhrba(char *str1, char *str2, char *str3)
// {
// 	if(str1)
// 	{
// 		write(....);
// 	}
// 	if(str2)
// 	{
// 		write(1, " ", 1);
// 		write(.....)
// 	}
// 	if(str3)
// 	{
// 		write(2, " ", 1);
// 		write(.....)
// 	}
// 	write(1, "\n", 1);
// }

int	ft_cd(char *path)
{
	char	*home;
	int		ret;

	if (!path || path[0] == '\0')
	{
		home = getenv("HOME");
		if (!home)
		{
			write(2, "bash: cd:", 5);
			write(2, " HOME not set\n", 5);
			return (1);
		}
		return(chdir(home));
	}
	else if (ft_strncmp(path, "..", 0))
		return (chdir(".."));
	else
	{
		ret = chdir(path);
		if (ret != 0)
		{
			write(2, "bash: cd:", 5);
			write(2, path, ft_strlen(path));
			write(2, ": No such file or directory\n", 28);
			return (1);
		}
	}
	return (0);
}
