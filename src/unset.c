/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:02 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/18 16:10:38 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**delete_line(t_shell *shell, int line)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = shell->env;
	while (shell->env[i])
	{
		if (i == line)
		{
			free(shell->env[i]);
			j = 1;
		}
		new[i] = shell->env[i + j];
		i++;
	}
	shell->env = new;
	i = 0;
	return (shell->env);
}

/*
int	env_size(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

char	**delete_line(t_shell *shell, int line)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * env_size(shell->env));
	while (shell->env[i])
	{
		if (i == line)
		{
			free(shell->env[i]);
			j = 1;
		}
		new[i] = shell->env[i + j];
		i++;
	}
	free(shell->env);
	shell->env = new;
	return (shell->env);
}
*/

void	delete_variable(char variable[FILENAME_MAX], char *name, t_shell *shell)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	while (shell->env[i] && ft_strlen(shell->env[i]) != 0)
	{
		j = 0;
		while (shell->env[i][j] != '=' && shell->env[i][j])
		{
			variable[j] = shell->env[i][j];
			j++;
		}
		variable[j] = '\0';
		if (ft_strcmp(name, variable) == 0)
		{
			shell->env = delete_line(shell, i);
			return ;
		}
		i++;
	}
}

char	*get_variable_name(char **args)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	name = malloc(sizeof(char) * (ft_strlen(args[1]) + 1));
	while (args[1][i] != '\0')
		*(name + j++) = args[1][i++];
	name[j] = '\0';
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

char	*unset(char **args, t_shell *shell)
{
	int		i;
	char	*name;
	char	variable[FILENAME_MAX];

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		return (NULL);
	name = get_variable_name(args);
	if (name == NULL)
		return (NULL);
	delete_variable(variable, name, shell);
	free(name);
	return (NULL);
}
