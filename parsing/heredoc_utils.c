/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:52:08 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/11 12:12:44 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	help_me(char *node, t_exp **exp, char *replace, int *i, int j)
{
	int		end;
	char	*value;

	if (node[*i] == '$')
		return (1);
	end = get_key(&node[*i]);
	value = get_value(&node[*i], end, exp);
	if (value)
	{
		while (*value)
		{
			replace[j] = *value;
			j++;
			value++;
		}
	}
	*i += end - 1;
	return (0);
}

char	*store_new_key2(char *node, int len, t_exp **exp)
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
		if (node[i] == '$' && (check_space(&node[i + 1])
				|| node[i + 1] == '\0'))
		{
			replace[j++] = node[i];
			break ;
		}
		else if (node[i] == '$')
		{
			i++;
			if (help_me(node, exp, &replace[j], &i, j) == 1)
				continue ;
		}
		else
			replace[j++] = node[i];
	}
	return (replace);
}

void	expanding_heredoc(char **read, t_exp **exp)
{
	int		i;
	int		len;
	char	*replace;

	i = 0;
	len = helper2(*read, exp);
	replace = store_new_key2(*read, len, exp);
	*read = ft_strdup(replace);
	free(replace);
}
