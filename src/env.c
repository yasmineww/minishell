/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:51:55 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/12 21:08:29 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_exp *exp)
{
	t_exp *tmp;

	while (exp)
	{
		tmp = exp;
		exp = exp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	print_env(t_exp *exp)
{
	while (exp)
	{
		printf("%s=%s\n", exp->key, exp->value);
		exp = exp->next;
	}
}

void find_key_value(char **envp, t_exp *exp)
{
	int i;
	int j;
	int l;

	i = 0;
	j = 0;
	l = 0;
	while (envp[i][l] != '=' && envp[i][l])
		l++;
	exp->key = malloc(sizeof(char) * (l + 1));
	if (!exp->key)
		return ;
	while (j < l)
	{
		exp->key[j] = envp[i][j];
		j++;
	}
	exp->key[j] = '\0';
	j = 0;
	l++;
	exp->value = malloc(sizeof(char) * (ft_strlen(envp[i]) - l + 1));
	if (!exp->value)
		return ;
	while (envp[i][l])
		exp->value[j++] = envp[i][l++];
	exp->value[j] = '\0';
}

int	ft_env(t_exp **exp, char **envp, int flag)
{
	int i;
	t_exp *tmp;
	t_exp *new;

	if (!flag)
		if (*exp)
			return(1);
	i = 0;
	*exp = NULL;
	while (envp[i])
	{
		tmp = *exp;
		new = malloc(sizeof(t_exp));
		if (!new)
			return (0);
		find_key_value(&envp[i], new);
		new->next = NULL;
		if (!tmp)
			*exp = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		i++;
	}
	if (flag)
		print_env(*exp);
	// free_env(*exp);
	return (1);
}
