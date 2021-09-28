/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:59:45 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 14:53:29 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env(char **args, t_shell *shell)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
	{
		printf("env: invalid number of arguments\n");
		return (NULL);
	}
	i = 0;
	while (shell->env[i])
	{
		if (ft_strlen(shell->env[i]) == 0)
			break ;
		write(1, shell->env[i], ft_strlen(shell->env[i]));
		write(1, "\n", 2);
		i++;
	}
	return (NULL);
}
