/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenchel <mbenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:16 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/05/11 22:29:16 by mbenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int ac,char **av ,char **envp)
{
    (void)ac;
	(void)av;
    char    *input;

    while(1)
    {
        input = readline("Minishell$ ");
        add_history(input);
        syntax_error(input);
    }
}
