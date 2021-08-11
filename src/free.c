/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:58:47 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 12:09:15 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freeArgs(char *line, t_shell *shell)
{
	int	i;

	if (ft_strlen(line) != 0)
	{
		free(line);
		i = 0;
		while (shell->args[i])
			free(shell->args[i++]);
		free(shell->args);
	}
}

void	free_and_exit(char **args, char *line)
{
	int		i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(line);
	free(args);
	exit(EXIT_SUCCESS);
}