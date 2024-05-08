/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:15:05 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/08 18:26:01 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*find_envp(char **envp)
// {
// 	int		i;
// 	char	*fullpath;

// 	i = 0;
// 	fullpath = NULL;
// 	while (envp[i] && envp[i][0] != '\0')
// 	{
// 		fullpath = ft_strnstr(envp[i], "PATH=", 5);
// 		if (fullpath)
// 			return (ft_substr(fullpath, 5, ft_strlen(fullpath)));
// 		i++;
// 	}
// 	return (NULL);
// }

char	*find_key_value(t_env *env, char **envp)
{
	int		i;
	int		j;
	int		l;

	j = 0;
	i = 0;
	l = 0;
	while (envp[i] && envp[i][0])
	{
		while (envp[i][l] != '=')
		{
			env->key[j] = envp[i][l];
		}
	}
	return (NULL);
}
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	find_key_value(envp);
}
