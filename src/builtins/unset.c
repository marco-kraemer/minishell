/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:02 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 14:54:28 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*get_variable_name(char *args)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	name = malloc(sizeof(char) * (ft_strlen(args) + 1));
	while (args[i] != '\0')
		*(name + j++) = args[i++];
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

char	*unset(char **args, t_shell *shell, int index)
{
	char	*name;
	char	variable[FILENAME_MAX];

	while (!args[index])
		return (NULL);
	name = get_variable_name(args[index]);
	if (name == NULL)
		return (NULL);
	delete_variable(variable, name, shell);
	free(name);
	return (unset(args, shell, index + 1));
}
