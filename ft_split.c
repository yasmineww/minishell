/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:03:30 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/13 20:28:00 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(const char *str, char c)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != c)
		{
			count++;
			while (*str && *str != c)
				str++;
		}
		else
			str++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, int n)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)malloc (n + 1);
	if (!str)
		return (0);
	while (i < n && s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	free_me(char **fresh, int i)
{
	if (!fresh)
		return ;
	while (i >= 0)
	{
		free (fresh[i]);
		fresh[i] = NULL;
		i--;
	}
	free (fresh);
	fresh = NULL;
}

static char	**help(char const *s, char c, int words, char **fresh)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *) s;
	while (i < words)
	{
		while (*s == c)
		{
			s++;
			str++;
		}
		if (*s == '\0')
			break ;
		while (*s != c && *s != '\0')
			s++;
		fresh[i] = ft_strndup(str, (s - str));
		if (!fresh[i++])
		{
			free_me(fresh, i);
			return (0);
		}
		str = (char *)s;
	}
	return (fresh);
}

char	**ft_split(char const *s, char c)
{
	char	**fresh;
	int		words;

	words = count_word(s, c);
	fresh = (char **) malloc((words + 1) * sizeof(char *));
	if (!fresh)
		return (0);
	help(s, c, words, fresh);
	fresh[words] = 0;
	return (fresh);
}
