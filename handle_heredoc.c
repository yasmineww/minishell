/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:04:17 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/23 16:03:02 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	long	m;

	m = n;
	size = ft_intlen(n);
	ptr = (char *) malloc (size + 1);
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

static char	*helper_join(char *s1, char *s2, char *ptr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	helper_join(s1, s2, ptr);
	return (ptr);
}

void	find_delimiter(t_list *temp, t_exp **exp, int i)
{
	int			fd;
	static int	num;
	char		*read;
	char		*file;

	file = ft_strjoin("/tmp/.here_doc", ft_itoa(num++));
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	temp->heredoc = fd;
	if (fd == -1) {
		perror("Failed to open file");
		return ;
	}
	read = readline("> ");
	while (read)
	{
		if (read[0] == '\0' && temp->option[i + 1] == NULL)
			break ;
		expanding_heredoc(&read, exp);
		if (!ft_strcmp(temp->option[i + 1], read))
			break ;
		read = readline("> ");
	}
	close(fd);
}

void	handle_heredoc(t_list **list, t_exp **exp)
{
	t_list	*temp;
	int		i;

	temp = *list;
	while (temp)
	{
		i = 0;
		while (temp->option[i])
		{
			if (!ft_strcmp(temp->option[i], "<<"))
				find_delimiter(temp, exp, i);
			i++;		
		}
		temp = temp->next;
	}
}
