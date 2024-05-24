/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:01:13 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/24 16:26:36 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	char	**option;
	char	*cmd;
	int		infile;
	int		outfile;
	struct s_list	*next;
}	t_list;

typedef struct s_exp
{
	char	**path;
	char	*key;
	char	*value;
	char	*oldpwd;
	struct s_exp *next;
}	t_exp;

// ---------------------- parsing ----------------------

int		count_arg(char *str);
int		error_message(char *input);
int		ft_strcmp(char *s1, char *s2);
int		special_char(char *ptr);
int		check_space(char *ptr);
int		two_specials(char *ptr);
int		delimiter(char *ptr);
int		syntax_error(char *ptr);
int		special_last(char *ptr);
int		cases(char *ptr, int i);
int		helper(char *ptr);
char	**ft_split(char const *s, char c);
char	**ft_split_spaces(char *s);
void	add_back(t_list **stack_a, char *content);
void	store_cmd(char *input, t_list **list);
void	split_cmd(t_list **list, char *input);
int		quotes_syntax_error(char *input);
int		count_quote(char *input);
char	*add_space(char *input);
int		ft_env(t_exp **exp, char **envp);
int		ft_strlen(char	*av);
void	parsing(char *input, t_list **list);
void	expanding(t_list **list, t_exp **exp);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, int start, int len);
int		ft_isalpha_num(char c);
int		get_key(char *ptr);
char	*get_value(char *ptr, int end, t_exp **exp);
void	handle_heredoc(t_list **list, t_exp **exp);
int		ft_intlen(int n);
void	expanding_heredoc(char **read, t_exp **exp);
int		helper2(char *tmp, t_exp **exp);
int		get_value_len(char *ptr, int j, int end, t_exp **exp);
char	*store_new_key(char *node, int len, t_exp **exp);
char	*ft_strtrim(char *s1, char *set);
void	ft_putendl_fd(char *s, int fd);

#endif