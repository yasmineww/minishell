/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:52:08 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/23 13:08:46 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expanding_heredoc(char **read, t_exp **exp)
{
	int		i;
	int		len;
	char	*replace;

	i = 0;
	while (read[0][i])
	{
		printf("|%c|\n",read[0][i]);
		if (read[0][0] != '\'')
		{
			len = helper2(read[0], exp);
			replace = store_new_key(read[0], len, exp);
			read[0] = ft_strdup(replace);
			free(replace);
		}
		i++;
	}
}
