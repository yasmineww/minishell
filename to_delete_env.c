/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:43:35 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/17 15:16:49 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_key_value(char *envp, t_exp *exp)
{
	int j;
	int l;

	j = 0;
	l = 0;
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
	j = 0;
	l++;
	exp->value = malloc(sizeof(char) * (ft_strlen(envp) - l + 1));
	if (!exp->value)
		return ;
	while (envp[l])
		exp->value[j++] = envp[l++];
	exp->value[j] = '\0';
}

int	ft_env(t_exp **exp, char **envp)
{
	int i;
	t_exp *tmp;
	t_exp *new;

	i = 0;
	*exp = NULL;
	while (envp[i])
	{
		tmp = *exp;
		new = malloc(sizeof(t_exp));
		if (!new)
			return (0);
		find_key_value(envp[i], new);
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
	// free_env(*exp);
	return (1);
}
