/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:58:05 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 12:21:15 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigintHandler_process(int sig_num)
{
	if (sig_num != SIGINT)
		return ;
	printf("\n");
	signal(SIGINT, sigintHandler_process);
}

void	sigintHandler(int sig_num)
{
	if (sig_num != SIGINT)
		return ;
	printf("\n");
	ft_putstr_fd(PROMPT_MSG, 1);
	signal(SIGINT, sigintHandler);
}

void	sigquitHandler(int sig_num)
{
	if (sig_num != SIGQUIT)
		return ;
	signal(SIGQUIT, sigquitHandler);
}
