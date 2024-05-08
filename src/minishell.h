/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:32 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/08 17:58:58 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../utils/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

typedef struct s_env
{
	char **path;
	char *key;
	char *value;
}	t_env;

typedef struct s_exp
{
	char *key;
	char *value;
	char *oldpwd;
} t_exp;

int		execute(char **envp, char **cmd, t_env *env);
char	*find_envp(char **envp);
int		is_builtin(t_env *env, char **cmd);
int		ft_cd(char *path);
int		ft_pwd(void);
char	*find_key_value(char **envp);


#endif
