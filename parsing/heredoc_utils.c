/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:52:08 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/29 10:03:41 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_with_value_heredoc(char *node, t_exp *exp, char *replace, int *j)
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

int	store_dollar_heredoc(char *node, char *replace, int i)
{
	int	j;

	j = 0;
	if (node[i] == '$' && (check_space(&node[i + 1])
			|| node[i + 1] == '\0'))
	{
		replace[j] = node[i];
		return (1);
	}
	return (0);
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

char	*store_new_key2(char *node, int len, t_exp *exp, t_mini *mini)
{
	int		i;
	int		j;
	char	*replace;

	i = -1;
	j = 0;
	replace = ft_calloc (1, len + 1);
	if (!replace)
		return (NULL);
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
			i += replace_with_value_heredoc(node + i + 1, exp, replace, &j);
			i++;
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
	replace = store_new_key2(*read, len, mini->exp, mini);
	free(*read);
	*read = ft_strdup(replace);
	free(replace);
}
