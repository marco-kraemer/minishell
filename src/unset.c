/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:02 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/11 11:15:37 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**delete_line(char **env, int line)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = env;
	while (env[i])
	{
		if (i == line)
			j = 1;
		new[i] = env[i + j];
		i++;
	}
	new[i - 1] = "\0";
	env = new;
	i = 0;
	return (env);
}

void	delete_variable(char *variable, char *name, char **env, char **args)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	variable = malloc(sizeof(char) * ft_strlen(args[1]));
	while (env[i] && ft_strlen(env[i]) != 0)
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j])
		{
			variable[j] = env[i][j];
			j++;
		}
		variable[j] = '\0';
		if (ft_strcmp(name, variable) == 0)
		{
			env = delete_line(env, i);
			free(variable);
			return ;
		}
		i++;
	}
	free(name);
}

char	*get_variable_name(char **args)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	name = malloc(sizeof(char) * ft_strlen(args[1]));
	while (args[1][i] != '\0')
		*(name + j++) = args[1][i++];
	name[j + 1] = '\0';
	i = 0;
	while (name[i])
	{
		if (name[i] == '=')
		{
			printf("unset: %s: not a valid identifier\n", name);
			return (NULL);
		}
		i++;
	}
	return (name);
}

char	*unset(char **args, char **env)
{
	int		i;
	char	*name;
	char	*variable;

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		return (NULL);
	name = get_variable_name(args);
	if (name == NULL)
		return (NULL);
	variable = NULL;
	delete_variable(variable, name, env, args);
	return (NULL);
}
