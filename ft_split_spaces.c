/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:03:30 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/16 18:57:01 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word_spaces(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (!check_space(str))
		{
			count++;
			while (*str && !check_space(str))
				str++;
		}
		else
			str++;
	}
	return (count);
}

static char	*ft_strndup(char *s, int n)
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

static char	**help_spaces(char *s, int words, char **fresh)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *) s;
	while (i < words)
	{
		while (check_space(s))
		{
			s++;
			str++;
		}
		if (*s == '\0')
			break ;
		while (!check_space(s) && *s != '\0')
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

char	**ft_split_spaces(char *s)
{
	char	**fresh;
	int		words;

	words = count_word_spaces(s);
	fresh = (char **) malloc((words + 1) * sizeof(char *));
	if (!fresh)
		return (0);
	help_spaces(s, words, fresh);
	fresh[words] = 0;
	return (fresh);
}
