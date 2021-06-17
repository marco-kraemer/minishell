/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:05 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/17 09:23:59 by maraurel         ###   ########.fr       */
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
	env[i][j++] = '\0';
	i++;
	env[i] = malloc(sizeof(char) * 1);
	env[i][0] = '\0';
	return (env);
}

char	*export(char **args, char **env)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	name[FILENAME_MAX];
	char	value[FILENAME_MAX];
	char	*ret;

	i = 0;
	while (args[i])
		i++;
	if (i == 1 || ft_strcmp(args[1], ">") == 0) // LIST VARIABLES
	{
		i = 0;
		size = 0;
		while (env[i + 1])
			size += ft_strlen(env[i++]);
		ret = malloc(sizeof(char) * size);
		i = 0;
		j = 0;
		while (env[i + 1])
		{
			k = 0;
			while (env[i][k])
				*(ret + j++) = env[i][k++];
			*(ret + j++) = '\n';
			i++;
		}
		*(ret + (j - 1)) = '\0';
		i = 0;
		return (ret);
	}
	else // ADD / CHANGE VARIABLES
	{
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
				return (NULL);
			}
			i++;
		}
		// ADD VARIABLES
		i = 0;
		env = add_line(env, name, value);
	}
	return (NULL);
}
