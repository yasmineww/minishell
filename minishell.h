/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:01:13 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/13 20:29:07 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	char			**cmd;
	struct s_list	*next;
}	t_list;

int		count_arg(char *str);
int		error_message(void);
int		ft_strcmp(char *s1, char *s2);
int		special_char(char *ptr);
int		check_space(char *ptr);
void	two_specials(char *ptr);
int		delimiter(char *ptr);
void	syntax_error(char *ptr);
void	special_last(char *ptr);
int		helper(char *ptr);
char	**ft_split(char const *s, char c);

#endif