/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:00:58 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/26 21:20:43 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_signals(int i)
{
	if (i == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

int	onecmd_builtin(t_mini *mini)
{
	int		std_in;
	int		std_out;

	std_in = dup(0);
	std_out = dup(1);
	if (!mini->list || !mini->list->option || mini->list->next)
		return (mini->status = 1, 1);
	if (handle_redirs(mini))
		return (1);
	exec_builtin(mini, mini->list->option);
	dup2(std_in, 0);
	dup2(std_out, 1);
	close(std_in);
	close(std_out);
	return (0);
}

void	update_underscore(t_exp **exp, char *last_arg)
{
	t_exp	*tmp;
	t_exp	*new;

	tmp = *exp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "_"))
		{
			free(tmp->value);
			if (!last_arg)
				tmp->value = ft_strdup("");
			else
				tmp->value = ft_strdup(last_arg);
			return ;
		}
		tmp = tmp->next;
	}
	if (!last_arg)
		new = create_node("_", "");
	else
		new = create_node("_", last_arg);
	if (new)
		ft_lstadd_back(exp, new);
}

char	*get_last_arg(char **option)
{
	int	i;

	i = 0;
	if (!option || !option[0])
		return (NULL);
	while (option[i + 1])
		i++;
	return (option[i]);
}
