/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:50:33 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/10 16:12:23 by ymakhlou         ###   ########.fr       */
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
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	catch_signal(void)
{
	signal(SIGINT, signal_handler1);
	signal(SIGQUIT, signal_handler2);
}

void	signal_handler_doc(int sig)
{
	(void) sig;
	if (sig == SIGINT)
	{
		g_sig = 1;
		// (*exp)->status = 1;
		close(0);
	}
}