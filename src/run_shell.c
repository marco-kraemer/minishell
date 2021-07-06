/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:07 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 09:38:04 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch(char **parsed, char **envp, char *file, char *msg)
{
	pid_t	pid;
	int	ret;
	int	status;

	pid = fork();
	signal(SIGINT, sigintHandler_process);
	if (pid == -1)
	{
		printf("Failed forking child..\n");
		return ;
	}
	else if (pid == 0)
	{
		if ((ret = execve(parsed[0], parsed, envp)) < 0)
			printf("%s: %s\n", file, msg);
		exit(ret);
	}
	else
	{
		wait(&status);
		return ;
	}
}

char	*execute(t_shell *shell, char **envp, char *line)
{
	char	*ret;

	ret = NULL;
	if (!shell->splited)
		return (NULL);
	if (ft_strcmp(shell->splited[0], "cd") == 0)
		return (change_directory(shell->splited));
	else if (ft_strcmp(shell->splited[0], "echo") == 0)
		ret = echo(shell, envp);
	else if (ft_strcmp(shell->splited[0], "export") == 0)
		ret = export(shell->splited, envp);
	else if (ft_strcmp(shell->splited[0], "unset") == 0)
		return (unset(shell->splited, envp));
	else if (ft_strcmp(shell->splited[0], "env") == 0)
		ret = env(shell->splited, envp);
	else if (ft_strcmp(shell->splited[0], "exit") == 0)
		free_and_exit(shell->splited, line);
	else if (ft_strncmp(shell->splited[0], "./", 2) == 0)
	{
		launch(shell->splited, envp, shell->splited[0], "No such file or directory");
		return (NULL);
	}
	else
	{
		ret = shell->splited[0];
		if (ft_strncmp("/bin/", shell->splited[0], 5) != 0)
			shell->splited[0] = ft_strjoin("/bin/", shell->splited[0]);
		launch(shell->splited, envp, ret, "command not found");
	}
	return (ret);
}
