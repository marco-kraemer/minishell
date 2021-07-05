/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:07 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/05 10:41:05 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch(char **parsed, char **envp, char *file, char *msg)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, sigintHandler_process);
	if (pid == -1)
	{
		printf("Failed forking child..\n");
		return ;
	}
	else if (pid == 0)
	{
		if (execve(parsed[0], parsed, envp) < 0)
			printf("%s: %s\n", file, msg);
		exit(0);
	}
	else
	{
		wait(NULL);
		return ;
	}
}

char	*execute(char **args, char **envp, char *line)
{
	char	*ret;

	ret = NULL;
	if (!args)
		return (NULL);
	if (ft_strcmp(args[0], "cd") == 0)
		return (change_directory(args));
	else if (ft_strcmp(args[0], "export") == 0)
		ret = export(args, envp);
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset(args, envp));
	else if (ft_strcmp(args[0], "env") == 0)
		ret = env(args, envp);
	else if (ft_strcmp(args[0], "exit") == 0)
		free_and_exit(args, line);
	else if (ft_strncmp(args[0], "./", 2) == 0)
	{
		launch(args, envp, args[0], "No such file or directory");
		return (NULL);
	}
	else
	{
		ret = args[0];
		if (ft_strncmp("/bin/", args[0], 5) != 0)
			args[0] = ft_strjoin("/bin/", args[0]);
		launch(args, envp, ret, "command not found");
	}
	return (ret);
}
