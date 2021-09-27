/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:05 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/27 01:35:07 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_line(t_shell *shell, char *name, char *value)
{
	int		i;
	char	*tmp;
	char	*var;

	tmp = ft_strjoin(name, "=");
	var = ft_strjoin(tmp, value);
	i = 0;
	while (shell->env[i])
		i++;
	if (i >= 9999)
	{
		printf("Error\n");
		return ;
	}
	*(shell->env + i) = ft_strdup(var);
	*(shell->env + (i + 1)) = NULL;
	free(tmp);
	free(var);
	free(name);
	free(value);
}

char	*get_name(char *args)
{
	int	i;

	i = 0;
	while (args[i] != '=')
		i++;
	return (ft_substr(args, 0, i));
}

char	*get_value(char *args)
{
	int	i;
	int	length;

	i = 0;
	while (args[i] != '=')
		i++;
	length = 0;
	while (args[i + length])
		length++;
	return (ft_substr(args, i + 1, length));
}

void	change_variable(t_shell *shell, char *name, char *value, int i)
{
	int		oldsize;
	int		newsize;
	char	*tmp1;
	char	*tmp2;

	oldsize = 0;
	while (shell->env[i][oldsize])
		oldsize++;
	newsize = 0;
	while (shell->env[i][newsize] != '=')
		newsize++;
	newsize += ft_strlen(value);
	free(shell->env[i]);
	tmp1 = ft_strjoin(name, "=");
	tmp2 = ft_strjoin(tmp1, value);
	shell->env[i] = ft_strdup(tmp2);
	free(tmp1);
	free(tmp2);
	free(name);
	free(value);
}

char	*insert_variable(char **args, t_shell *shell, int index)
{
	int		i;
	int		j;
	char	*name;
	char	*value;

	if (!args[index])
		return (NULL);
	name = get_name(args[index]);
	value = get_value(args[index]);
	i = 0;
	while (shell->env[i] && ft_strlen(shell->env[i]) != 0)
	{
		j = 0;
		while (shell->env[i][j] != '=' && shell->env[i][j])
			j++;
		if (ft_strncmp(name, shell->env[i], ft_strlen(name)) == 0
			&& j == (int)ft_strlen(name))
		{
			change_variable(shell, name, value, i);
			return (insert_variable(args, shell, index + 1));
		}
		i++;
	}
	add_line(shell, name, value);
	return (insert_variable(args, shell, index + 1));
}

char	*no_value_case(t_shell *shell)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (shell->env[i])
	{
		name = get_name(shell->env[i]);
		value = get_value(shell->env[i]);
		if (ft_strlen(shell->env[i]) == 0)
			break ;
		printf("declare -x %s=\"%s\"\n", name, value);
		free(name);
		free(value);
		i++;
	}
	return (NULL);
}

char	*export(char **args, t_shell *shell, int index)
{
	if (!args[1])
		return (no_value_case(shell));
	else
		return (insert_variable(args, shell, index));
}
