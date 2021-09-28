/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:58:47 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 17:34:45 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	check_numeric_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static	int	check_exit_arg(char **args, int *mark)
{
	int	i;
	int	status;

	i = 0;
	*mark = 0;
	while (args[i])
		i++;
	if (i == 1)
		status = 0;
	else if (i == 2)
	{
		status = 2;
		if (check_numeric_arg(args[1]))
			status = ft_atoi(args[1]);
		else
			printf("bash: exit: %s: numeric argument required\n", args[1]);
	}
	else
	{
		printf("shell: exit: too many arguments\n");
		g_status = 1;
		*mark = -1;
		return (-1);
	}
	return (status);
}

void	free_and_exit(char **args, char *line, t_shell *shell)
{
	int	i;
	int	mark;
	int	status;

	i = 0;
	status = check_exit_arg(shell->splited, &mark);
	if (mark == -1)
		return ;
	while (args[i])
		free(args[i++]);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strlen(shell->env[i]) == 0)
			break ;
		free(shell->env[i++]);
	}
	free(shell->env);
	free(shell->quote_rules);
	free(line);
	free(args);
	exit(status);
}

void	ft_free_double(char **s)
{
	int	i;

	i = 0;
	if (!s)
	{
		free(s);
		return ;
	}
	while (s[i])
		free(s[i++]);
	free(s);
}

char	**to_free2(char const **p, int j)
{
	while (j >= 0)
	{
		free((void *)p[j]);
		j--;
	}
	free(p);
	return (NULL);
}
