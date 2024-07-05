/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:04:20 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/05 11:52:55 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_quotes(char *s1, int *bool)
{
	char	*copy;
	int		i;

	copy = malloc (ft_strlen(s1) + 1);
	i = 0;
	if (!s1 || !copy)
		return (NULL);
	while (*s1)
	{
		if (*s1 == '\'' || *s1 == '"')
		{
			s1++;
			*bool = 1;
		}
		else
		{
			copy[i] = *s1;
			i++;
			s1++;
		}
	}
	copy[i] = '\0';
	return (copy);
}
void	protect_fd(char *file)
{
	perror("Failed to open file");
	free(file);
	return ;
}

void	signal_handler_doc(int sig)
{
	(void) sig;
	close(0);
}

void	find_delimiter(t_list *temp, t_exp **exp, int i)
{
	static int	num;
	char		*read;
	char		*file;
	int			bool;
	char		*delim;

	file = ft_strjoin(".here_doc", ft_itoa(num++));
	temp->infile = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (temp->infile == -1)
		return (protect_fd(file));
	if (temp->option[i + 1][0] == '$')
		delim = rm_quotes((temp->option[i + 1] + 1), &bool);
	else
		delim = rm_quotes((temp->option[i + 1]), &bool);
	int fd = dup(0);
	signal(SIGINT, signal_handler_doc);
	read = readline("> ");
	while (read)
	{
		if (!bool)
			expanding_heredoc(&read, exp);
		if (!ft_strcmp(delim, read))
			break ;
		ft_putendl_fd(read, temp->infile);
		free(read);
		read = readline("> ");
	}
	dup2(fd, 0);
	close(fd);
	free(read);
	free(delim);
	close(temp->infile);
	if (isatty(0))
		temp->infile = -3;
	else
	{
		temp->infile = open(file, O_RDONLY, 0644);
		if (temp->infile == -1)
			return (protect_fd(file));
	}
	unlink(file);
	free(file);
}

void	handle_heredoc(t_list **list, t_exp **exp)
{
	t_list		*temp;
	int			i;
	int			j;

	temp = *list;
	if (temp)
		temp->infile = 0;
	j = 0;
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
