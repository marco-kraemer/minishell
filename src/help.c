/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:35:21 by user42            #+#    #+#             */
/*   Updated: 2021/06/09 14:38:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_variable_list(char **env)
{
	int		i;
	char	**new;

	i = 0;
	while (env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (env[i])
	{
		new[i] = malloc(sizeof(char) * ft_strlen(env[i]));
		i++;
	}
	new[i] = malloc(1);
	new[i] = "\0";
	i = 0;
	while (env[i])
	{
		new[i] = env[i];
		i++;
	}
	return (new);
}

int	free_and_exit(char **args, char *line)
{
	int		i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(line);
	free(args);
	exit(EXIT_SUCCESS);
}