/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:53:32 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/05 09:50:57 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*c;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	c = (char *)malloc(len + 1);
	if (c == NULL)
		return (NULL);
	while (s1[j])
		c[i++] = s1[j++];
	j = 0;
	while (s2[j])
		c[i++] = s2[j++];
	c[i] = '\0';
	return (c);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

int	isalpha_underscore(int c, int flag)
{
	if (flag == 1)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
			return (1);
		return (0);
	}
	else
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| c == '_' || (c >= '0' && c <= '9'))
			return (1);
	return (0);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*b;
	unsigned char	v;
	size_t			i;

	b = (unsigned char *)s;
	v = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		b[i] = v;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	if (n == 0)
		return ;
	ft_memset(s, 0, n);
}
