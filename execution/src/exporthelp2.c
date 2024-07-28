/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporthelp2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:43:03 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/28 08:01:15 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exp	*last_node(t_exp *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int	exporthelp(t_mini *mini, char **s)
{
	t_exp	*new;
	int		i;

	i = 1;
	if (!s[1])
	{
		new = dup_list(mini->exp);
		sort_list(new);
		print_exp(new);
		free_env(new);
	}
	else if (s[1] && mini->exp)
	{
		while (s[i])
		{
			export(mini, s[i]);
			i++;
		}
	}
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
