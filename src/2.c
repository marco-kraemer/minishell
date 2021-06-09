/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:02 by user42            #+#    #+#             */
/*   Updated: 2021/06/09 14:37:35 by user42           ###   ########.fr       */
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
	new[i - 2] = "\0";
	env = new;
	i = 0;
	return (env);
}

int	unset(char **args, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*name;
	char	*variable;

	// GET VARIABLE NAME
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
			return (0);
		}
		i++;
	}
	// DELETE VARIABLE
	i = 0;
	k = 0;
	variable = malloc(sizeof(char) * ft_strlen(args[1]));
	while (env[i])
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
			return (1);
		}
		i++;
	}
	free(name);
	printf("\n");
	return (1);
}