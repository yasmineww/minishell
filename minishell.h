/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:48:59 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/11 17:09:24 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "execution/utils/utils.h"
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

int	g_sig;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_list
{
	char			**option;
	char			*cmd;
	int				infile;
	int				outfile;
	struct s_list	*next;
}	t_list;

typedef struct s_exp
{
	int				ambiguous;
	int				status;
	char			**path;
	char			*key;
	char			*value;
	char			*oldpwd;
	char			*pwd;
	struct s_exp	*next;
}	t_exp;

// ---------------------- utils ----------------------

int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(char *s, int start, int len);
int		ft_isalpha_num(char c);
int		ft_intlen(int n);
void	*ft_calloc(size_t count, size_t size);
int		count_word_spaces(char *str);

// ---------------------- parsing ----------------------

int		error_message(char *input, t_exp **exp);
int		special_char(char *ptr);
int		check_space(char *ptr);
int		two_specials(char *ptr);
int		delimiter(char *ptr);
int		syntax_error(char *ptr);
int		special_last(char *ptr);
int		cases(char *ptr, int i);
int		helper(char *ptr);
char	**ft_split_spaces(char *s);
void	add_back(t_list **stack_a, char *content);
void	store_cmd(char *input, t_list **list);
void	split_cmd(t_list **list, char *input);
int		quotes_syntax_error(char *input);
int		count_quote(char *input);
char	*add_space(char *input);
int		ft_env(t_exp **exp, char **envp);
int		parsing(char *input, t_list **list, t_exp **exp);
void	expanding(t_list **list, t_exp **exp);
int		get_key(char *ptr);
char	*get_value(char *ptr, int end, t_exp **exp);
void	handle_heredoc(t_list **list, t_exp **exp);
void	expanding_heredoc(char **read, t_exp **exp);
int		helper2(char *tmp, t_exp **exp);
int		get_value_len(char *ptr, int j, int end, t_exp **exp);
char	*store_new_key(char *node, int len, t_exp **exp);
int		found_question_mark(char node, t_exp **exp, char *replace);
int		store_dollar(char *node, char *replace, int i);
int		replace_with_value(char *node, t_exp **exp, char *replace, int *i);

// ---------------------- execution ----------------------

int		execute(t_list *list, t_exp *exp, char **envp);
int		is_builtin(char **cmd);
int		exec_builtin(t_exp **exp, char **cmd);
int		ft_cd(char *path, t_exp *exp);
int		ft_pwd(t_exp *exp);
int		countparams(char **s);
void	print_env(t_exp **exp);
int		ft_echo(char **cmd, t_exp *exp);
int		exec(t_exp *exp, t_list *list, char **envp);
int		ft_unset(t_exp **exp, char *key);
int		export(t_exp **exp, char *s);
void	find_key(char *envp, t_exp *exp);
int		exporthelp(t_exp *exp, char **s);
void	sort_list(t_exp *exp);
void	print_exp(t_exp *exp);
t_exp	*dup_list(t_exp *exp);
int		handle_redir_in(t_list *list, int i, t_exp *exp);
int		handle_redir_out(t_list *list, int i, t_exp *exp);
int		handle_append(t_list *list, int i, t_exp *exp);
int		ft_lstsize(t_list *lst);
void	handle_redirs(t_list *list, t_exp *exp);
char	*find_path(t_exp *exp);
void	ft_error(char *str1, char *str2, char *str3);
int		ft_exit(char **cmd, t_exp *exp);
int		ft_isnumber(char *s);

// ---------------------- signals ----------------------

void	signal_handler1(int sig);
void	signal_handler2(int sig);
void	catch_signal(void);
void	signal_handler_doc(int sig);

#endif
