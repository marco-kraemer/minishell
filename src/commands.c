/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 11:07:20 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *name, char **env)
{
	int	i;
	int	j;
	char	*value;

	i = 0;
	value = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j);
			return (value);
		}
		i++;
	}
	return (value);
}

char	**correct_args(t_shell *shell, int status, char **envp)
{
	int	i;
	char	*value;
	char	*tmp;

	i = 0;
	while (shell->splited[i])
	{
		if (shell->splited[i][0] == '$' && shell->quote_rules[i] != 2)
		{
			if (ft_strncmp(shell->splited[i], "$?", ft_strlen(shell->splited[i])) == 0)
				value = ft_itoa(status);
			else
			{
				tmp = ft_substr(shell->splited[i], 1, ft_strlen(shell->splited[i]));
				value = ft_getenv(tmp, envp);
			}
			if (value)
				shell->splited[i] = value;
			else
				shell->splited[i] = NULL;
		}
		i++;
	}
	return (shell->splited);
}

char	*echo(t_shell *shell, int status,char **envp)
{
	pid_t pid;

	shell->splited = correct_args(shell, status, envp);
	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return (NULL);
	}
	else if (pid == 0) 
	{
		if (execve("/bin/echo", shell->splited, NULL) < 0)
			printf("%s: No such file or directory\n", shell->splited[0]);
		exit(0);
	}
	else
	{
		wait(NULL); 
		return (NULL);
	}
	return (NULL);
}

char	*change_directory(char **args)
{
	if (args[1] == NULL)
		chdir("");
	else
	{
		if (chdir(args[1]) != 0)
			printf("shell: No such file or directory\n");
	}
	return (NULL);
}

char	*env(char **args, char **env)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
	{
		printf("env: invalid number of arguments\n");
		return (NULL);
	}
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
