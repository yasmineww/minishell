/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:52:08 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/29 11:08:38 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_val_heredoc(char *node, t_exp *exp, char *replace, int *j)
{
	int		end;
	char	*value;

	end = get_key(node);
	value = get_value(node, end, exp);
	if (value)
	{
		while (*value)
		{
			replace[*j] = *value;
			(*j)++;
			value++;
		}
	}
	return (end - 1);
}

int	found_quest_heredoc(char node, t_mini *mini, char *replace, int *j)
{
	char	*value;
	int		i;

	i = 0;
	if (node == '?')
	{
		value = ft_itoa(mini->status);
		while (value[i])
		{
			replace[(*j)++] = value[i];
			i++;
		}
		free(value);
		return (1);
	}
	return (0);
}

char	*store_new_key2(char *node, char *replace, t_mini *mini, int j)
{
	int	i;

	i = -1;
	while (node[++i])
	{
		if (node[i] == '$')
		{
			if (node[i + 1] && node[i + 1] == '$')
			{
				i++;
				continue ;
			}
			else if (found_quest_heredoc(node[i + 1], mini, replace, &j) && ++i)
				continue ;
			else if (!node[i + 1] || !ft_isalpha_num(node[i + 1]))
			{
				replace[j++] = node[i];
				continue ;
			}
			i += replace_val_heredoc(node + i + 1, mini->exp, replace, &j) + 1;
		}
		else
			replace[j++] = node[i];
	}
	return (replace);
}

void	expanding_heredoc(char **read, t_mini *mini)
{
	int		len;
	char	*replace;

	len = helper2(*read, mini);
	replace = ft_calloc (1, len + 1);
	if (!replace)
		return ;
	replace = store_new_key2(*read, replace, mini, 0);
	free(*read);
	*read = ft_strdup(replace);
	free(replace);
}
