/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:53:55 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/01 15:22:50 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	number_args(char **str)
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
	if (i != number_args(shell->env))
	{
		path = ft_substr(shell->env[i], 5, ft_strlen(shell->env[i]));
		path_args = ft_split(path, ':');
		free(path);
	}
	return (path_args);
}

void	cd_empty_argument(char *home)
{
	if (home)
	{
		chdir(home);
		free(home);
	}
	else
	{
		g_status = 1;
		printf("shell: cd: HOME not set\n");
	}
}
