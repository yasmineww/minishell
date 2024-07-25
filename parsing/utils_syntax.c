/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:57:59 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/23 23:34:14 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_message(char *input, int *status)
{
	write(2, "Minishell: syntax error\n", 25);
	*status = 258;
	free(input);
	input = NULL;
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	special_char(char *ptr)
{
	if (*ptr == '|' || *ptr == '<' || *ptr == '>'
		|| (ft_strcmp(ptr, "<<") == 0) || (ft_strcmp(ptr, ">>") == 0))
		return (1);
	return (0);
}

int	check_space(char *ptr)
{
	if ((*ptr >= 9 && *ptr <= 13) || *ptr == 32)
		return (1);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (count > 9223372036854775807 || size > 9223372036854775807)
		return (0);
	ptr = malloc (count * size);
	if (!ptr)
		return (NULL);
	while (i < (count * size))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
