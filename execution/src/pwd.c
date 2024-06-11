/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:36:54 by mbenchel          #+#    #+#             */
/*   Updated: 2024/06/11 23:28:20 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_exp *exp)
{
	if (getcwd(NULL, 0)) // check the leaks
	{
		printf("%s\n", getcwd(NULL, 0));
		return (0);
	}
	else
		printf("%s\n", exp->pwd);
	return (0);
}
