/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:58:05 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/12 10:58:14 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigintHandler_process(int sig_num)
{
	(void)sig_num;
	g_status = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sigintHandler(int sig_num)
{
	(void)sig_num;
	g_status = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquitHandler(int sig_num)
{
	(void)sig_num;
	signal(SIGQUIT, sigquitHandler);
}
