/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:05 by user42            #+#    #+#             */
/*   Updated: 2021/06/09 14:37:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**add_line(char **env, char *name, char *value)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (env[i + 1])
		i++;
	env[i] = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2));
	j = 0;
	while (name[j])
	{
		env[i][j] = name[j];
		j++;
	}
	env[i][j++] = '=';
	k = 0;
	while (value[k])
	{
		env[i][j] = value[k];
		j++;
		k++;
	}
	i++;
	env[i] = malloc(sizeof(char) * 1);
	env[i][0] = '\0';
	return (env);
}

int	export(char **args, char **env)
{
	int		i;
	int		j;
	char	name[FILENAME_MAX];
	char	value[FILENAME_MAX];

	i = 0;
	while (args[i])
		i++;
	if (i == 1) // LIST VARIABLES
	{	
		i = 0;
		while (env[i + 1])
			printf("%s\n", env[i++]);
	}
	else // ADD / CHANGE VARIABLES
	{
		i = 0;
		// GET VARIABLE VALUE
		while (args[1][i] != '=')
			i++;
		i++;
		j = 0;
		while (args[1][i])
			value[j++] = args[1][i++];
		value[j++] = '\0';
		// GET VARIABLE NAME
		i = 0;
		j = 0;
		while (args[1][i] != '=')
			name[j++] = args[1][i++];
		name[i] = '\0';
		// CHANGE VARIABLE VALUE
		i = 0;
		while (env[i])
		{
			j = 0;
			while (env[i][j] != '=' && env[i][j])
				j++;
			if (ft_strncmp(name, env[i], ft_strlen(name)) == 0 && j == (int)ft_strlen(name))
			{
				int k = 0;
				j = 0;
				while (env[i][j] != '=')
					j++;
				j++;
				while (value[k])
					env[i][j++] = value[k++];
				env[i][j++] = '\0';
				return (1);
			}
			i++;
		}
		// ADD VARIABLES
		i = 0;
		env = add_line(env, name, value);
	}
	return (1);
}