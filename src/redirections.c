/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:57:44 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/17 10:00:23 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	redirect_output(char *filename, char *data)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY |O_TRUNC, 0777);
	if (data != NULL)
		write (fd, data, ft_strlen(data));
	close(fd);
}

void	append_output(char *filename, char *data)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (data != NULL)
		write (fd, data, ft_strlen(data));
	close(fd);
}

int	check_redirection(char **args, char *value)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0)
		{
			redirect_output(args[i + 1], value);
			return (0);
		}
		else if (ft_strcmp(args[i], ">>") == 0)
		{
			append_output(args[i + 1], value);
			return (0);
		}
		i++;
	}
	return (1);
}
