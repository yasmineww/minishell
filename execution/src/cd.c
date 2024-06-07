/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:36:55 by mbenchel          #+#    #+#             */
/*   Updated: 2024/06/07 17:41:27 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_error(char *str1, char *str2, char *str3)
{
	if (str1)
		write(2, str1, ft_strlen(str1));
	if (str2)
	{
		write(2, " ", 1);
		write(2, str2, ft_strlen(str2));
	}
	if (str3)
	{
		write(2, ": ", 2);
		write(2, str3, ft_strlen(str3));
	}
	write(1, "\n", 1);
}

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
		return (chdir(home));
	}
	else if (!ft_strncmp(path, "..", 2))
		return (chdir(".."));
	else
	{
		ret = chdir(path);
		if (ret != 0)
			return (ft_error("bash: cd:", path, "No such file or directory")
				, 1);
	}
	return (0);
}
