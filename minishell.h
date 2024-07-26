/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:48:59 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/26 01:17:33 by mbenchel         ###   ########.fr       */
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
# include <dirent.h>

int	g_sig;

# define PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin"
# define UNDERSC "/usr/bin/env"

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

typedef struct s_flag
{
	int	ambiguous;
	int	special;
	int	expanded;
}	t_flag;

typedef struct s_list
{
	t_flag			flags;
	char			**option;
	char			*cmd;
	int				infile;
	int				outfile;
	int				oldpwd_unset;
	int				pwd_unset;
	struct s_list	*next;
}	t_list;

typedef struct s_exp
{
	int				test;
	int				expanded;
	int				status;
	int				ambiguous;
	char			**path;
	char			*key;
	char			*value;
	//char			*oldpwd; // still not sure i'll be working with this
	// char			*pwd;
	struct s_exp	*next;
}	t_exp;

typedef struct s_mini
{
	char	*pwd;
	int		is_quote;
	int		status;
	char	*replace;
	t_list	*list;
	t_exp	*exp;
}	t_mini;

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
int		ft_2dlen(char **s);
int		isalpha_underscore(int c, int flag);
t_exp	*create_node(char *key, char *value);
t_exp	*last_node(t_exp *head);
int		ft_isnumber(char *s);
void	sort_list(t_exp *exp);
int		countparams(char **s);
t_exp	*dup_list(t_exp *exp);
void	ft_error(char *str1, char *str2, char *str3);


// ---------------------- parsing ----------------------

int		parsing(t_mini *mini, char *input);
int		error_message(char *input, int *status);
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
void	expanding(t_mini *mini, int i, int count);
int		get_key(char *ptr);
char	*get_value(char *ptr, int end, t_exp *exp);
void	handle_heredoc(t_mini *mini);
void	expanding_heredoc(char **read, t_mini *mini);
int		helper2(char *tmp, t_mini *mini);
int		get_value_len(char *ptr, int j, int end, t_exp *exp);
int		found_quest(char node, t_mini *mini, int *j);
int		store_dollar(char *node, char *replace, int i);
int		replace_with_value(t_list *list, char *node, t_mini *mini, int *j);
void	free_list(t_list *list);

// ---------------------- execution ----------------------

int		execute(t_mini *mini, char **envp);
int		is_builtin(char **cmd);
int		exec_builtin(t_mini *mini, char **cmd);
int		ft_cd(char *path, t_mini *mini);
int		ft_pwd(t_mini *mini);
void	print_env(t_exp **exp);
int		ft_echo(char **cmd, t_exp *exp, t_mini *mini);
int		exec(t_mini *mini, char **envp, struct termios *term);
int		ft_unset(t_mini *mini, char *key);
int		export(t_mini *mini, char *s);
void	find_key(char *envp, t_exp *exp);
int		exporthelp(t_mini *mini, char **s);
void	print_exp(t_exp *exp);
int		handle_redir_in(t_mini *mini, int i);
int		handle_redir_out(t_mini *mini, int i);
int		handle_append(t_mini *mini, int i);
int		handle_redirs(t_mini *mini);
char	*find_path(t_exp **exp);
int		ft_exit(char **cmd, t_mini *mini);
void	free_env(t_exp *exp);
char	*ft_getoldpwd(t_exp *exp);
void	cwd_oldpwd(t_exp *exp, char *cwd, char *oldpwd);
int		find_home(t_exp *exp, t_mini *mini);
int		ft_find_home(t_exp *exp, t_mini *mini);
void	update_cwd(t_mini *mini);
void	parent_io(t_exec *data, t_list *list);
char	*get_cmd_path(t_exp *exp, char *cmd, t_mini *mini);
int		onecmd_builtin(t_mini *mini);
void	child_io(t_exec *data, t_list *list);
int		ft_unset_helper(t_mini *mini, char **s);
void	setup_signals(int i);

// ---------------------- signals ----------------------

void	signal_handler(int sig);
void	signal_handler_heredoc(int sig);

#endif
