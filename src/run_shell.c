/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:07 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/11 15:02:26 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch(t_shell *shell, char **envp, char *file, char *msg)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	signal(SIGINT, sigintHandler_process);
	if (pid == -1)
	{
		printf("Failed forking child..\n");
		return ;
	}
	else if (pid == 0)
	{
		ret = execve(shell->splited[0], shell->splited, envp);
		if (ret < 0)
			printf("%s: %s\n", file, msg);
		exit(ret);
	}
	else
	{
		wait(&shell->status);
		if (WEXITSTATUS(shell->status))
			shell->status = WEXITSTATUS(shell->status);
		return ;
	}
}

char	*launch_prog(t_shell *shell, char **envp)
{
	if (ft_strncmp(shell->splited[0], "./", 2) == 0)
		launch(shell, envp, shell->splited[0], "No such file or directory");
	else
	{
		if (ft_strncmp("/bin/", shell->splited[0], 5) != 0)
			shell->splited[0] = ft_strjoin("/bin/", shell->splited[0]);
		launch(shell, envp, shell->splited[0], "command not found");
	}
	return (NULL);
}

void	execute_child(t_shell *shell, char **envp, char *line)
{
	char		*ret;
	static int	prev_status;

	ret = NULL;
	if (!shell->splited)
		return ;
	if (ft_strcmp(shell->splited[0], "cd") == 0)
		change_directory(shell->splited);
	else if (ft_strcmp(shell->splited[0], "echo") == 0)
		echo(shell, prev_status, envp);
	else if (ft_strcmp(shell->splited[0], "export") == 0)
		export(shell->splited, envp);
	else if (ft_strcmp(shell->splited[0], "unset") == 0)
		unset(shell->splited, envp);
	else if (ft_strcmp(shell->splited[0], "env") == 0)
		 env(shell->splited, envp);
	else if (ft_strcmp(shell->splited[0], "exit") == 0)
		free_and_exit(shell->splited, line);
	else
		launch_prog(shell, envp);
	prev_status = shell->status;
}

void	pipe_fdout_fdin(t_shell *shell, int fdpipe[2], int i)
{
	dup2(shell->fdin, 0);
	close(shell->fdin);
	if (i == shell->numcommands - 1)
	{
		if (shell->rule == 1 || shell->rule == 13 || shell->rule == 5)
			shell->fdout = open(shell->outfile, O_CREAT
					| O_WRONLY | O_TRUNC, 0777);
		else if (shell->rule == 7 || shell->rule == 17 || shell->rule == 11)
			shell->fdout = open(shell->outfile, O_CREAT
					| O_WRONLY | O_APPEND, 0777);
		else
			shell->fdout = dup(shell->tmpout);
	}
	else
	{
		pipe(fdpipe);
		shell->fdout = fdpipe[1];
		shell->fdin = fdpipe[0];
	}
	dup2(shell->fdout, 1);
	close(shell->fdout);
}

void	execute(t_shell *shell, char **env)
{
	int	i;
	int	fdpipe[2];
	int	ret;

	i = 0;
	while (i < shell->numcommands)
	{
		pipe_fdout_fdin(shell, fdpipe, i);
		if (shell->numcommands != 1)
			ret = fork();
		else
			ret = 0;
		if (ret == 0)
		{
			shell->splited = split_args(shell->args[i], shell);
			execute_child(shell, env, NULL);
			free(shell->splited);
			if (shell->numcommands != 1)
				exit (EXIT_SUCCESS);
		}
		else
			wait(NULL);
		i++;
	}
}
