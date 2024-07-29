/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:51:55 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/29 12:03:05 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(t_exp **exp)
{
	t_exp	*tmp;

	tmp = *exp;
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	find_value(char *env, t_exp *exp, int l)
{
	int	j;

	j = 0;
	if (!env[l])
	{
		exp->value = NULL;
		return ;
	}
	exp->value = malloc(sizeof(char) * (ft_strlen(env) - l + 1));
	if (!exp->value)
		return ;
	while (env[l])
		exp->value[j++] = env[l++];
	exp->value[j] = '\0';
}

void	find_key(char *envp, t_exp *exp)
{
	int	l;
	int	j;

	l = 0;
	j = 0;
	while (envp[l] != '=' && envp[l])
		l++;
	exp->key = malloc(sizeof(char) * (l + 1));
	if (!exp->key)
		return ;
	while (j < l)
	{
		exp->key[j] = envp[j];
		j++;
	}
	exp->key[j] = '\0';
	find_value(envp, exp, l + 1);
}

void	check_oldpwd(t_exp *exp)
{
	if (!ft_strcmp(exp->key, "OLDPWD"))
	{
		if (exp->value)
			free(exp->value);
		exp->value = NULL;
	}
}

int	ft_env(t_exp **exp, char **envp)
{
	int			i;
	t_exp		*new;

	i = -1;
	*exp = NULL;
	if (!envp || !*envp)
		return (setup_env_ignored(exp, NULL));
	while (envp[++i])
	{
		new = malloc(sizeof(t_exp));
		if (!new)
			return (exit(1), 1);
		find_key(envp[i], new);
		check_oldpwd(new);
		new->next = NULL;
		ft_lstadd_back(exp, new);
	}
	return (1);
}
