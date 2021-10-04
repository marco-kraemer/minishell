/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:58:05 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/02 10:38:59 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler_process(int sig_num)
{
	(void)sig_num;
	g_status = -1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sigquit_handler_process(int sig_num)
{
	(void)sig_num;
	g_status = -2;
	printf("Quit (core dumped)\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	g_status = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
