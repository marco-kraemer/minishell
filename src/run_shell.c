/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:07 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/07 08:47:50 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch(t_shell *shell, char **envp, char *file, char *msg)
{
	pid_t	pid;
	int	ret;

	pid = fork();
	signal(SIGINT, sigintHandler_process);
	if (pid == -1)
	{
		printf("Failed forking child..\n");
		return ;
	}
	else if (pid == 0)
	{
		if ((ret = execve(shell->splited[0], shell->splited, envp)) < 0)
			printf("%s: %s\n", file, msg);
		exit(ret);
	}
	else
	{
		wait(&shell->status);
		shell->status = WEXITSTATUS(shell->status);
		return ;
	}
}

char	*execute_child(t_shell *shell, char **envp, char *line)
{
	char	*ret;
	static int	prev_status;

	ret = NULL;
	if (!shell->splited)
		return (NULL);
	if (ft_strcmp(shell->splited[0], "cd") == 0)
		return (change_directory(shell->splited));
	else if (ft_strcmp(shell->splited[0], "echo") == 0)
		ret = echo(shell, prev_status,envp);
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
		launch(shell, envp, shell->splited[0], "No such file or directory");
		return (NULL);
	}
	else
	{
		ret = shell->splited[0];
		if (ft_strncmp("/bin/", shell->splited[0], 5) != 0)
			shell->splited[0] = ft_strjoin("/bin/", shell->splited[0]);
		launch(shell, envp, ret, "command not found");
	}
	prev_status = shell->status;
	return (ret);
}
