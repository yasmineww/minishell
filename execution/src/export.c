/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:49:21 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/26 20:26:42 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// i might need to add protections 7it list t9d tkon empty

int	ft_new_key(t_exp **exp, char *s, t_mini *mini)
{
	t_exp	*cur;
	t_exp	*new;

	cur = *exp;
	while (cur)
	{
		if (ft_strcmp(cur->key, s) == 0)
			return (0);
		cur = cur->next;
	}
	new = malloc(sizeof(t_exp));
	if (!new)
		return (mini->status = 1, 1);
	new->key = ft_strdup(s);
	new->value = NULL;
	new->next = NULL;
	ft_lstadd_back(exp, new);
	return (0);
}

int	ft_append_value(t_exp **exp, char *s, int i, t_mini *mini)
{
	t_exp	*cur;
	t_exp	*new;

	cur = *exp;
	while (cur)
	{
		if (ft_strncmp(cur->key, s, i - 1) == 0 && cur->key[i] == '\0')
		{
			if (cur->value)
				cur->value = ft_strjoin(cur->value, s + i + 2);
			else
				cur->value = ft_strdup(s + i + 2);
			return (0);
		}
		cur = cur->next;
	}
	new = malloc(sizeof(t_exp));
	if (!new)
		return (mini->status = 1, 1);
	new->key = ft_substr(s, 0, i);
	new->value = ft_strdup(s + i + 2);
	new->next = NULL;
	ft_lstadd_back(exp, new);
	return (0);
}

int	ft_export_input(const char *s)
{
	int	i;

	i = 0;
	if (s[i] && !isalpha_underscore(s[i], 1))
		return (1);
	while (s[i] && s[i] != '+' && s[i] != '=')
	{
		if (!isalpha_underscore(s[i], 0))
			return (1);
		i++;
	}
	return (0);
}

int	ft_reset_value(t_exp **exp, char *s, int i, t_mini *mini)
{
	t_exp	*cur;
	t_exp	*new;

	cur = *exp;
	while (cur)
	{
		if (ft_strncmp(cur->key, s, i - 1) == 0 && cur->key[i] == '\0')
		{
			if (cur->value)
				free(cur->value);
			cur->value = ft_strdup(s + i + 1);
			return (0);
		}
		cur = cur->next;
	}
	new = malloc(sizeof(t_exp));
	if (!new)
		return (mini->status = 1, 1);
	new->key = ft_substr(s, 0, i);
	new->value = ft_strdup(s + i + 1);
	new->next = NULL;
	ft_lstadd_back(exp, new);
	return (0);
}

int	export(t_mini *mini, char *s)
{
	int		i;

	i = 0;
	if (!ft_strncmp(s, "PWD", 3))
		mini->pwd_unset = 0;
	if (!ft_strncmp(s, "OLDPWD", 6))
		mini->oldpwd_unset = 0;
	if (ft_export_input(s))
		return (ft_error("export", s, "not a valid identifier\n"),
			mini->status = 1, 1);
	while (s[i] && s[i] != '+' && s[i] != '=')
		i++;
	if (s[i] == '+' && s[i + 1] == '=')
		return (ft_append_value(&mini->exp, s, i, mini));
	else if (s[i] == '=')
		return (ft_reset_value(&mini->exp, s, i, mini));
	else if (!ft_strchr(s, '=') && !ft_strchr(s, '+'))
		return (ft_new_key(&mini->exp, s, mini));
	return (0);
}
