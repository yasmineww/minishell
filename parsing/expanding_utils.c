/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:26:36 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/24 16:17:34 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	int		i;
	size_t	len;
	char	*copy;

	i = 0;
	len = ft_strlen(s1);
	copy = (char *) malloc (len + 1);
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_substr(char *s, int start, int len)
{
	char			*ptr;
	int			i;
	int		size;

	size = 0;
	if (!s)
		return (0);
	i = 0; 
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	while (s[start + size] && size < len)
		size++;
	ptr = (char *) malloc (size + 1);
	if (!ptr)
		return (NULL);
	while (s[start + i] && i < size)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_isalpha_num(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || 
		(c >= 'a' && c <= 'z'))
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}
char	*get_value(char *ptr, int end, t_exp **exp)
{
	char	*ptr2;
	t_exp	*env;

	env = *exp;
	ptr2 = ft_substr(ptr, 0, end);
	if (!ptr2)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, ptr2))
		{
			free(ptr2);          
			return (env->value);
		}
		env = env->next;
	}
	free(ptr2);
	return (NULL);
}

int	get_key(char *ptr)
{
	int	i;

	i = 0;
	while (ft_isalpha_num(ptr[i]))
		i++;
	return (i);
}
