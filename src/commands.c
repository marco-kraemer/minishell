/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/05 19:10:35 by maraurel         ###   ########.fr       */
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
		if (ft_strncmp(env[i], name, j) == 0)
		{
			value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j);
			return (value);
		}
		i++;
	}
	return (value);
}

char	**correct_args(char **args, char **envp, t_shell shell)
{
	int	i;
	char	*value;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && shell.quote_rules[i] != 2)
		{
			tmp = ft_substr(args[i], 1, ft_strlen(args[i]));
			value = ft_getenv(tmp, envp);
			if (value)
				args[i] = value;
			else
				args[i] = NULL;
		}
		i++;
	}
	return (args);
}

char	*echo(char **args, char **envp, t_shell *shell)
{
	pid_t pid;

	args = correct_args(args, envp, *shell);
	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return (NULL);
	}
	else if (pid == 0) 
	{
		if (execve("/bin/echo", args, NULL) < 0)
			printf("%s: No such file or directory\n", args[0]);
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
