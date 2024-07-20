/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:48:59 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/19 13:26:57 by ymakhlou         ###   ########.fr       */
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

typedef struct s_exec
{
	int	fdpipe[2];
	int	std_in;
	int	std_out;
	int	*pid;
	int	status;
	int	i;
	int	count;
}	t_exec;
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
	int				expanded;
	int				status;
	char			**path;
	char			*key;
	char			*value;
	//char			*oldpwd; // still not sure i'll be working with this
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
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_exp **head, t_exp *new);

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
int		found_question_mark(char node, t_exp **exp, char *replace, int *j);
int		store_dollar(char *node, char *replace, int i);
int		replace_with_value(char *node, t_exp **exp, char *replace, int *i);

// ---------------------- execution ----------------------

int		execute(t_list *list, t_exp **exp, char **envp);
int		is_builtin(char **cmd);
int		exec_builtin(t_exp **exp, char **cmd);
int		ft_cd(char *path, t_exp *exp);
int		ft_pwd(t_exp *exp);
int		countparams(char **s);
void	print_env(t_exp **exp);
int		ft_echo(char **cmd, t_exp *exp);
int		exec(t_exp **exp, t_list *list, char **envp, struct termios *term);
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
int		handle_redirs(t_list *list, t_exp *exp);
char	*find_path(t_exp **exp);
void	ft_error(char *str1, char *str2, char *str3);
int		ft_exit(char **cmd, t_exp *exp);
int		ft_isnumber(char *s);
void	free_env(t_exp *exp);
char	*ft_getoldpwd(t_exp *exp);
void	cwd_oldpwd(t_exp *exp, char *cwd, char *oldpwd);
int		find_home(t_exp *exp);
int		ft_find_home(t_exp *exp);
void	update_cwd(t_exp *exp);
t_exp	*last_node(t_exp *head);
void	parent_io(t_exec *data, t_list *list);
char	*get_cmd_path(t_exp *exp, char *cmd);
void	setup_signals(int i);
int		onecmd_builtin(t_exp **exp, t_list *list);
void	child_io(t_exec *data, t_list *list);
int		ft_unset_helper(t_exp **exp, char **s);

// ---------------------- signals ----------------------

void	signal_handler(int sig);
void	signal_handler_heredoc(int sig);

#endif
