/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:32 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/24 16:12:47 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H



#include "execution/utils/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>

typedef struct s_exp
{
	char **path;
	char *key;
	char *value;
	char *oldpwd;
	struct s_exp *next;
}	t_exp;

typedef struct s_list
{
	char			**option;
	char			*cmd;
	int infile;
	int outfile;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

typedef struct s_flag
{
	int sorted_flag;
	int null_flag;
}	t_flag;

int		execute(t_list *list, t_exp *exp, char **envp);
char	*find_path(char **envp);
int		is_builtin(char **cmd);
int		exec_builtin(t_exp **exp, char **cmd);
int		ft_cd(char *path);
int		ft_pwd(void);
int		ft_env(t_exp **exp, char **envp);
// int		ft_env(t_exp **exp, char **envp, int flag);
int		countparams(char **s);
void	print_env(t_exp **exp);
int		ft_echo(char **cmd);
int		exec(t_exp *exp, t_list *list);
int		ft_unset(t_exp **exp, char *key);
int		export(t_exp **exp, char *s);
void	find_key_value(char **envp, t_exp *exp);
int		exporthelp(t_exp *exp, char *s);
void	sort_list(t_exp *exp);
void	print_exp(t_exp *exp);
t_exp	*dup_list(t_exp *exp);
int		handle_redir(t_list *list);
int		ft_lstsize(t_list *lst);
#endif
