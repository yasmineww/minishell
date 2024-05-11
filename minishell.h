/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:01:13 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/11 21:27:00 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/utils.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_exp
{
	char **path;
	char *key;
	char *value;
	char *oldpwd;
	struct s_exp *next;
}	t_exp;

// ---------------------- parsing ----------------------

int		count_arg(char *str);
int		error_message();
int		ft_strcmp(char *s1, char *s2);
int		special_char(char *ptr);
int		check_space(char *ptr);
void	two_specials(char *ptr);
int		delimiter(char *ptr);
void    syntax_error(char *ptr);
void	special_last(char *ptr);
int		helper(char *ptr);

// ---------------------- execution ----------------------

int		execute(char **envp, char **cmd, t_exp *exp);
char	*find_path(char **envp);
int		is_builtin(t_exp **exp, char **cmd, char **envp);
int		ft_cd(char *path);
int		ft_pwd(void);
int		ft_env(t_exp **exp, char **envp);
int		countparams(char **s);
void	print_env(t_exp *exp);
int		ft_echo(char **cmd);

#endif
