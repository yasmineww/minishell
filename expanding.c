/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:39:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/21 12:41:57 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
char	*get_value(char *ptr, int end, t_exp **exp)
{
	char	*ptr2;
	t_exp	*env;

	printf("ptr --->%s\n", ptr);
	printf("end is %d\n", end);
	env = *exp;
	ptr2 = ft_substr(ptr, 0, end);
	printf("ptr2 --->%s\n", ptr2);
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

int	get_key(char *ptr)
{
	int	i;

	i = 0;
	while (ft_isalpha_num(ptr[i]))
		i++;
	return (i);
}

char	*store_new_key(char *node, int len, t_exp **exp)
{
	int		i;
	int		j;
	int		end;
	char	*replace;
	char	*value;

	i = -1;
	j = 0;
	replace = calloc (1, len + 1);
	if (!replace)
		return NULL;
	while (node[++i])
	{
		if (node[i] == '$')
		{
			i++;
			end = get_key(&node[i]);
			printf("end before %d\n", end);
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

int	get_value_len(char *ptr, int j, int end, t_exp **exp)
{
	char	*ptr2;
	t_exp	*env;

	env = *exp;
	ptr2 = ft_substr(ptr, j, end);
	if (!ptr2)
		return 0;
	while (env)
	{
		if (!ft_strcmp(env->key, ptr2))
			return (ft_strlen(env->value));
		env = env->next;
	}
	return (0);
}

// void	replace_key()

void	expanding(t_list **list, t_exp **exp)
{
	int		i;
	int		j;
	int		end;
	int		len;
	t_list	*tmp;
	char	*replace;

	tmp = *list;
	while (tmp)
	{
		i = 0;
		while (tmp->option[i])
		{
			len = ft_strlen(tmp->option[i]);
			j = -1;
			while (tmp->option[i][++j])
			{
				if (tmp->option[i][j] == '$')
				{
					end = get_key(&tmp->option[i][j + 1]);
					len += get_value_len(tmp->option[i], j + 1, end, exp);
				}
			}
			replace = store_new_key(tmp->option[i], len, exp);
			// printf("new_expand :%s\n", replace);
			tmp->option[i] = ft_strdup(replace);
			free(replace);
			i++;
		}
		tmp = tmp->next;
	}
}
