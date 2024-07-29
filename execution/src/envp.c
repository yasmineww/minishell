/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:15:05 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/29 12:02:58 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_path(t_exp **exp)
{
	t_exp	*tmp;

	tmp = *exp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_exp	*create_node(char *key, char *value)
{
	t_exp	*new;

	new = malloc(sizeof(t_exp));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

int	setup_env_ignored(t_exp **exp, char *pwd)
{
	t_exp	*new;

	pwd = getcwd(NULL, 0);
	new = create_node("PWD", pwd);
	free(pwd);
	if (!new)
		return (exit(1), 1);
	ft_lstadd_back(exp, new);
	new = create_node("SHLVL", "1");
	if (!new)
		return (exit(1), 1);
	ft_lstadd_back(exp, new);
	new = create_node("OLDPWD", NULL);
	if (!new)
		return (exit(1), 1);
	ft_lstadd_back(exp, new);
	new = create_node("HOME", UNDERSC);
	if (!new)
		return (exit(1), 1);
	ft_lstadd_back(exp, new);
	new = create_node("PATH", PATH);
	if (!new)
		return (exit(1), 1);
	ft_lstadd_back(exp, new);
	return (0);
}

void	free_env(t_exp *exp)
{
	t_exp	*tmp;

	while (exp)
	{
		tmp = exp;
		exp = exp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
