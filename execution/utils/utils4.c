/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:12:03 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/25 13:06:14 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	my_atoi(char *str)
{
	long	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res);
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

void	ft_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
