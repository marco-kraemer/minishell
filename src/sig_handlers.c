/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:58:05 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/21 20:51:56 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler_process(int sig_num)
{
	(void)sig_num;
	g_status = 130;
	printf("\n");
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
