/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:52:08 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/10 12:20:06 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*store_new_key2(char *node, int len, t_exp **exp)
{
	int		i;
	int		j;
	int		end;
	char	*replace;
	char	*value;

	i = -1;
	j = 0;
	replace = ft_calloc (1, len + 1);
	if (!replace)
		return (NULL);
	while (node[++i])
	{
		if (node[i] == '$' && (check_space(&node[i + 1]) || node[i + 1] == '\0'))
		{
			replace[j++] = node[i];
			break ;
		}
		else if (node[i] == '$')
		{
			i++;
			if (node[i] == '$')
				continue ;
			end = get_key(&node[i]);
			value = get_value(&node[i], end, exp);
			if (value)
			{
				while (*value)
				{
					replace[j++] = *value;
					value++;
				}
			}
			i += end - 1;
		}
		else
			replace[j++] = node[i];
	}
	return (replace);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	long	m;

	m = n;
	size = ft_intlen(n);
	ptr = ft_calloc(1, size + 1);
	if (!ptr)
		return (NULL);
	ptr[size] = '\0';
	size--;
	if (m == 0)
		*ptr = '0';
	if (m < 0)
	{
		m = m * -1;
		ptr[0] = '-';
	}
	while (m > 0)
	{
		ptr[size] = (m % 10) + 48;
		m = m / 10;
		size--;
	}
	return (ptr);
}

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
	len = helper2(*read, exp);
	replace = store_new_key2(*read, len, exp);
	*read = ft_strdup(replace);
	free(replace);
}
