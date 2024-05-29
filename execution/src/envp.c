/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:15:05 by mbenchel          #+#    #+#             */
/*   Updated: 2024/05/27 18:04:03 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_path(t_exp *exp)
{
	while (exp)
	{
		if (!ft_strcmp(exp->key, "PATH"))
			return (exp->value);
		exp = exp->next;
	}
	return (NULL);
}

