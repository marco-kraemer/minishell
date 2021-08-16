/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:05 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/15 23:21:49 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_line(t_shell *shell, char name[FILENAME_MAX],
	char value[FILENAME_MAX])
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
}

char	*NoValueCase(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strlen(shell->env[i]) == 0)
			break ;
		write(1, shell->env[i], ft_strlen(shell->env[i]));
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

char	*change_variable(t_shell *shell, char name[FILENAME_MAX],
	char value[FILENAME_MAX], int i)
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
	return (NULL);
}

char	*export(char **args, t_shell *shell)
{
	int		i;
	int		j;
	char	name[FILENAME_MAX];
	char	value[FILENAME_MAX];

	if (!args[1])
		return (NoValueCase(shell));
	get_name_value(value, name, args);
	i = 0;
	while (shell->env[i] && ft_strlen(shell->env[i]) != 0)
	{
		j = 0;
		while (shell->env[i][j] != '=' && shell->env[i][j])
			j++;
		if (ft_strncmp(name, shell->env[i], ft_strlen(name)) == 0
			&& j == (int)ft_strlen(name))
			return (change_variable(shell, name, value, i));
		i++;
	}
	add_line(shell, name, value);
	return (NULL);
}
