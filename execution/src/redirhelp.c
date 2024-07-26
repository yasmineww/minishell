/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirhelp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:56:39 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/26 19:59:47 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_redir(char **option, int i)
{
	if (ft_2dlen(option) < 3)
	{
		free(option[i]);
		option[i] = NULL;
		if (option[i + 1])
		{
			free(option[i + 1]);
			option[i + 1] = NULL;
		}
		return ;
	}
	free(option[i]);
	free(option[i + 1]);
	while (option[i + 2])
	{
		option[i] = option[i + 2];
		i++;
	}
	option[i] = NULL;
	if (option[i + 1])
		option[i + 1] = NULL;
}

int	check_amb(t_mini *mini, int i)
{
	if (mini->list->flags.ambiguous)
	{
		ft_error("Minishell:", mini->list->option[i + 1],
			"ambiguous redirect\n");
		mini->list->flags.ambiguous = 0;
		mini->status = 1;
		return (1);
	}
	return (0);
}

int	process_redir(t_mini *mini, int *i, char *type, int (*handler)
	(t_mini *, int))
{
	int	res;

	res = redirs_handler(mini, *i, type, handler);
	if (res == 1)
		return (1);
	else if (res == 2)
		return (0);
	return (0);
}
