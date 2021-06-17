/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:57:44 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/17 08:52:48 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	redirect_input(char *filename, char *data)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY, 0777);
	write (fd, data, ft_strlen(data));
}

void	check_redirection(char **args, char *value)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0)
			redirect_input(args[i + 1], value);
		i++;
	}
}
