/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:50:33 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/11 18:21:20 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler2(int sig)
{
	(void) sig;
	printf("Quit: 3\n");
}

void	signal_handler1(int sig)
{
	(void) sig;
	g_sig = -10;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler_doc(int sig)
{
	(void) sig;
	if (sig == SIGINT)
	{
		g_sig = 1;
		close(0);
	}
}
