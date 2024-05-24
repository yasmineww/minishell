/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:42 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/24 17:15:57 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*c;
// 	size_t	slen;

// 	if (!s)
// 		return (NULL);
// 	slen = ft_strlen(s);
// 	if (s == NULL || start >= slen)
// 		return (ft_strdup(""));
// 	if (start + len > slen)
// 		len = slen - start;
// 	c = (char *)malloc((len + 1) * sizeof(char));
// 	if (c == NULL)
// 		return (NULL);
// 	ft_strlcpy(c, &s[start], len + 1);
// 	return (c);
// }

// static size_t	countwords(const char *s, char c)
// {
// 	size_t	i;
// 	size_t	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while (s[i] && s[i] == c)
// 			i++;
// 		if (s[i])
// 			count++;
// 		while (s[i] && s[i] != c)
// 			i++;
// 	}
// 	return (count);
// }

// static char	*getwords(int *i, const char *s, char c)
// {
// 	int		tpos;
// 	int		j;
// 	char	*word;

// 	j = 0;
// 	while (s[*i] && s[*i] == c)
// 		(*i)++;
// 	tpos = *i;
// 	while (s[*i] && s[*i] != c)
// 		(*i)++;
// 	word = malloc(sizeof(char) * (*i - tpos + 1));
// 	if (!word)
// 		return (NULL);
// 	while (tpos + j < *i)
// 	{
// 		word[j] = s[tpos + j];
// 		j++;
// 	}
// 	word[j] = '\0';
// 	return (word);
// }

// char	**ft_freew(char **s)
// {
// 	int	i;

// 	if (s)
// 	{
// 		i = 0;
// 		while (s[i])
// 		{
// 			free(s[i]);
// 			i++;
// 		}
// 		free(s);
// 	}
// 	return (NULL);
// }

// char	**ft_split(const char *s, char c)
// {
// 	char	**tab;
// 	int		i;
// 	int		j;
// 	int		wc;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	wc = countwords(s, c);
// 	tab = malloc(sizeof(char *) * (wc + 1));
// 	if (!tab)
// 		return (NULL);
// 	while (j < wc)
// 	{
// 		tab[j] = getwords(&i, s, c);
// 		if (!tab[j])
// 		{
// 			return (ft_freew(tab));
// 		}
// 		j++;
// 	}
// 	tab[j] = NULL;
// 	return (tab);
// }
