/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:59:45 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 12:00:44 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*env(char **args, char **env)
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
	while (env[i])
	{
		if (ft_strlen(env[i]) == 0)
			break ;
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 2);
		i++;
	}
	return (NULL);
}
