/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:05 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 12:15:45 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_line(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i + 1] && ft_strlen(env[i + 1]) != 0)
		i++;
	i++;
	env[i] = var;
	env[i + 1] = NULL;
}

char	*export(char **args, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*var;
	char	name[FILENAME_MAX];
	char	value[FILENAME_MAX];

	if (!args[1])
	{
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
	// GET VARIABLE NAME
	i = 0;
	j = 0;
	while (args[1][i] != '=' && args[1][i])
		name[j++] = args[1][i++];
	name[j] = '\0';
	// GET VARIABLE VALUE
	if (args[1][i] != '=')
		value[0] = '\0';
	else
	{
		i++;
		j = 0;
		while (args[1][i] && args[1][i])
			value[j++] = args[1][i++];
		value[j++] = '\0';
	}
	// CHANGE VARIABLE VALUE
	i = 0;
	while (env[i] && ft_strlen(env[i]) != 0)
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j])
			j++;
		if (ft_strncmp(name, env[i], ft_strlen(name)) == 0 && j == (int)ft_strlen(name))
		{
			k = 0;
			j = 0;
			while (env[i][j] != '=')
				j++;
			j++;
			while (value[k])
				env[i][j++] = value[k++];
			env[i][j++] = '\0';
			return (NULL);
		}
		i++;
	}
	// ADD VARIABLES
	var = ft_strjoin(name, "=");
	var = ft_strjoin(var, value);
	add_line(env, var);
	return (NULL);
}
