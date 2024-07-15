/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporthelp2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:43:03 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/14 23:44:31 by mbenchel         ###   ########.fr       */
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

int	exporthelp(t_exp *exp, char **s)
{
	t_exp	*new;
	int		i;

	i = 1;
	if (!s[1])
	{
		new = dup_list(exp);
		sort_list(new);
		print_exp(new);
	}
	else if (s[1] && exp)
	{
		while (s[i])
		{
			export(&exp, s[i]);
			i++;
		}
	}
	return (0);
}
