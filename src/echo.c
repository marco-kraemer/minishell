/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:57:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/16 10:26:24 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	value = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (ft_strncmp(env[i], name, j) == 0)
		{
			value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j);
			free(name);
			return (value);
		}
		i++;
	}
	free(name);
	return (value);
}

char	**correct_args(t_shell *shell, int status, char **envp, int i)
{
	char	*value;

	while (shell->splited[i])
	{
		if (shell->splited[i][0] == '$' && shell->quote_rules[i] != 2)
		{
			if (ft_strncmp(shell->splited[i], "$?",
					ft_strlen(shell->splited[i])) == 0)
				value = ft_itoa(status);
			else
				value = ft_getenv(ft_substr(shell->splited[i], 1,
							ft_strlen(shell->splited[i])), envp);
			free(shell->splited[i]);
			if (value)
				shell->splited[i] = value;
			else
				shell->splited[i] = NULL;
		}
		i++;
	}
	return (shell->splited);
}

char	*echo(t_shell shell, char **envp)
{
	pid_t	pid;

	shell.splited = correct_args(&shell, g_status, shell.env, 0);
	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return (NULL);
	}
	else if (pid == 0)
	{
		if (execve("/bin/echo", shell.splited, envp) < 0)
			printf("%s: No such file or directory\n", shell.splited[0]);
		exit(0);
	}
	else
	{
		wait(&g_status);
		if (WEXITSTATUS(g_status))
			g_status = 127;
	}
	return (NULL);
}
