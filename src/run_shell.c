/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:07 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/22 09:28:34 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch(char **parsed, char **envp)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return;
	}
	else if (pid == 0) 
	{
		if (ft_strlen(envp[0]) == 3535)
			printf("oi\n");
		if (execve(parsed[0], parsed, envp) < 0)
			printf("%s: No such file or directory\n", parsed[0]);
		exit(0);
	}
	else
	{
		wait(NULL); 
		return;
	}
}

char	*execute(char **args, char **envp, char *line)
{
	char	*ret;

	ret = NULL;
	if (args[0] == NULL)
		return (NULL);
	if (ft_strcmp(args[0], "cd") == 0)
		return (change_directory(args));
	else if (ft_strcmp(args[0], "echo") == 0)
		ret = (echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		ret = pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		ret = export(args, envp);
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset(args, envp));
	else if (ft_strcmp(args[0], "env") == 0)
		ret  = env(args, envp);
	else if (ft_strcmp(args[0], "exit") == 0)
		free_and_exit(args, line);
	else if (ft_strncmp(args[0], "./", 2) == 0)
	{
		launch(args, envp);
		return (NULL);
	}
	else
	{
		printf("%s: command not found\n", args[0]);
		return (NULL);
	}
	check_redirection(args, ret);
	return (ret);
}
