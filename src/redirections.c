/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:57:44 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/16 15:35:34 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	redirect_input(char **args, int count, char *value)
{
	int	fd;

	fd = open(value, O_RDONLY, 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	check_redirection(char **args, char *value)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0)
			redirect_input(args, i + 1, value);
		i++;
	}
}
