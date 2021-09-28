/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:05 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 14:28:19 by maraurel         ###   ########.fr       */
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
	while (args[i] != '=' && args[i])
	{
		if (ft_isalpha(args[i]) == 0 && args[i] != '_')
		{
			printf("export: '%s': not a valid identifier\n", args);
			return (NULL);
		}
		i++;
	}
	return (ft_substr(args, 0, i));
}

char	*get_value(char *args)
{
	int	i;
	int	length;

	i = 0;
	while (args[i] != '=' && args[i])
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

char	*insert_variable(char **args, t_shell *s, int index)
{
	char	*name;
	char	*value;

	if (!args[index])
		return (NULL);
	name = get_name(args[index]);
	if (!name)
		return (insert_variable(args, s, index + 1));
	value = get_value(args[index]);
	s->i = 0;
	while (s->env[s->i] && ft_strlen(s->env[s->i]) != 0)
	{
		s->j = 0;
		while (s->env[s->i][s->j] != '='&& s->env[s->i][s->j])
			s->j++;
		if (ft_strncmp(name, s->env[s->i], ft_strlen(name)) == 0
			&& s->j == (int)ft_strlen(name))
		{
			change_variable(s, name, value, s->i);
			return (insert_variable(args, s, index + 1));
		}
		s->i++;
	}
	add_line(s, name, value);
	return (insert_variable(args, s, index + 1));
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
		if (value[0])
			printf("declare -x %s=\"%s\"\n", name, value);
		else
			printf("declare -x %s\n", name);
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
