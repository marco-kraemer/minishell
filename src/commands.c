/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/22 12:09:22 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*echo(char **args)
{
	pid_t pid;

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

char	*pwd()
{
	char	cwd[FILENAME_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("getcwd() error\n");
	write(1, cwd, ft_strlen(cwd));	
	write(1, "\n", 2);
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
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 2);
		i++;
	}
	return (NULL);
}
