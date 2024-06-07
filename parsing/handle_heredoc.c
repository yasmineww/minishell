/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:04:17 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/06/06 23:01:42 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	find_delimiter(t_list *temp, t_exp **exp, int i)
{
	static int	num;
	char		*read;
	char		*file;
	int			bool;
	char		*ptr;

	bool = 0;
	if (temp->option[i + 1][0]== '"' || temp->option[i + 1][0]== '\'')
		bool = 1;
	file = ft_strjoin("here_doc", ft_itoa(num++));
	temp->infile = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	// unlink(file);
	if (temp->infile == -1) {
		perror("Failed to open file");
		free(file);
		return ;
	}
	read = readline("> ");
	while (read)
	{
		if (!bool)
			expanding_heredoc(&read, exp);
		ptr = ft_strtrim(temp->option[i + 1], "\'\"");
		if (!ft_strcmp(ptr, read))
		{
			free(ptr);
			break ;
		}
		free(ptr);
		ft_putendl_fd(read, temp->infile);
		free(read);
		read = readline("> ");
	}
	free(read);
	close(temp->infile);
	// this below is added by marin i am trying to fix a heredoc + redirection out case
	temp->infile = open(file, O_RDONLY, 0644);
	if (temp->infile == -1) {
		perror("Failed to open file");
		unlink(file);
		free(file);
		return ;
	}
	unlink(file);
	free(file);
}

void	handle_heredoc(t_list **list, t_exp **exp)
{
	t_list		*temp;
	here_doc	*var;
	int			i;
	int			count;

	temp = *list;
	var = malloc(sizeof(here_doc));
	count = 0;
	while (temp)
	{
		i = 0;
		while (temp->option[i])
		{
			if (!ft_strcmp(temp->option[i], "<<"))
			{
				var->delimiter = ft_strtrim(temp->option[i + 1], "\'\"");
				count++;
				printf("delimiter [%s] and count [%d]\n", var->delimiter, count);
				find_delimiter(temp, exp, i);
			}
			i++;
		}
		temp = temp->next;
	}
}
