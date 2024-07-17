/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:51:55 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/17 17:25:53 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	print_env(t_exp **exp)
{
	t_exp *tmp;

	tmp = *exp;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 6) == 0)
			tmp->value = NULL;// mazal hna lkhdma
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

int	ft_env(t_exp **exp, char **envp)
{
	int			i;
	t_exp		*tmp;
	t_exp		*new;

	i = -1;
	*exp = NULL;
	if (!envp)
		return (1);
	while (envp[++i])
	{
		new = malloc(sizeof(t_exp));
		if (!new)
			return (exit(1), 1);
		find_key(envp[i], new);
		new->next = NULL;
		if (!*exp)
			*exp = new;
		else
		{
			tmp = *exp;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	return ((*exp)->status = 1, 1);
}
