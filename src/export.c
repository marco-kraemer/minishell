/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:05 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/15 15:04:47 by maraurel         ###   ########.fr       */
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

char	*NoValueCase(char **env)
{
	int	i;

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

void	get_name_value(char value[FILENAME_MAX],
		char name[FILENAME_MAX], char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[1][i] != '=' && args[1][i])
		name[j++] = args[1][i++];
	name[j] = '\0';
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
}

char	*change_variable(char **env, char value[FILENAME_MAX], int i)
{
	int	k;
	int	j;

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

char	*export(char **args, char **env)
{
	int		i;
	int		j;
	char	name[FILENAME_MAX];
	char	value[FILENAME_MAX];

	if (!args[1])
		return (NoValueCase(env));
	get_name_value(value, name, args);
	i = 0;
	while (env[i] && ft_strlen(env[i]) != 0)
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j])
			j++;
		if (ft_strncmp(name, env[i], ft_strlen(name)) == 0
			&& j == (int)ft_strlen(name))
			return (change_variable(env, value, i));
		i++;
	}
	add_line(env, ft_strjoin(ft_strjoin(name, "="), value));
	return (NULL);
}
