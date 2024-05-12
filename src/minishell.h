/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:32 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/12 18:50:45 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../utils/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

typedef struct s_exp
{
	char **path;
	char *key;
	char *value;
	char *oldpwd;
	struct s_exp *next;
}	t_exp;

int		execute(char **envp, char **cmd, t_exp *exp);
char	*find_path(char **envp);
int		is_builtin(t_exp **exp, char **cmd, char **envp);
int		ft_cd(char *path);
int		ft_pwd(void);
int		ft_env(t_exp **exp, char **envp, int flag);
int		countparams(char **s);
void	print_env(t_exp *exp);
int		ft_echo(char **cmd);
int		execute(char **envp, char **cmd, t_exp *exp);
int		exec(t_exp *exp, char **envp, char **cmd);
int		ft_unset(t_exp **exp, char *key);

#endif
