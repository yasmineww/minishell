/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:52:08 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/23 17:38:57 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*copy;
	char	*end;
	char	*start;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (ft_strchr(set, *start) && *start)
		start++;
	while (ft_strchr(set, *end) && end > start)
		end--;
	copy = ft_substr(start, 0, end - start +1);
	return (copy);
}

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
