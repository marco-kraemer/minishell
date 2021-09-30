/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:53:55 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 10:54:11 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	number_args_path(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**find_path_value(t_shell *shell)
{
	int		i;
	char	*path;
	char	**path_args;

	i = 0;
	path_args = NULL;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (i != number_args_path(shell->env))
	{
		path = ft_substr(shell->env[i], 5, ft_strlen(shell->env[i]));
		path_args = ft_split(path, ':');
		free(path);
	}
	return (path_args);
}
