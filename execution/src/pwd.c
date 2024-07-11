/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:36:54 by mbenchel          #+#    #+#             */
/*   Updated: 2024/07/11 18:44:43 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_exp *exp)
{
	if (getcwd(NULL, 0))
	{
		printf("%s\n", getcwd(NULL, 0));
		return (0);
	}
	else
		printf("%s\n", exp->pwd);
	return (0);
}

//leaks
