/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:07 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/29 16:06:09 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	launch(t_shell *shell, char **envp, char **file, char *msg)
{
	pid_t	pid;
	int		ret;
	int		wait_status;

	pid = fork();
	signal(SIGINT, sigint_handler_process);
	signal(SIGQUIT, &sigquit_handler_process);
	if (pid == -1)
	{
		printf("Failed forking child.\n");
		return ;
	}
	else if (pid == 0)
	{
		if (contains_slash(shell->splited[0], &ret))
			ret = execve(shell->splited[0], shell->splited, envp);
		if (ret < 0)
			ret = iterate_over_path(shell, envp, file, msg);
		exit(ret);
	}
	else
	{
		wait(&wait_status);
		g_status = WEXITSTATUS(wait_status);
	}
}

char	*launch_prog(t_shell *shell, char **envp)
{
	int		i;
	char	**path_args;

	i = 0;
	path_args = ft_split(getenv("PATH"), ':');
	if (ft_strncmp(shell->splited[0], "./", 2) == 0)
		launch(shell, envp, path_args, "no such file or directory");
	else
		launch(shell, envp, path_args, "command not found");
	while (path_args[i])
		free(path_args[i++]);
	free(path_args);
	return (NULL);
}

void	execute_child(t_shell *shell, char **envp, char *line)
{
	char		*ret;
	static int	prev_status;

	ret = NULL;
	if (!shell->splited)
		return ;
	if (!shell->splited[0])
		return ;
	if (ft_strcmp(shell->splited[0], "cd") == 0)
		change_directory(shell->splited);
	else if (ft_strcmp(shell->splited[0], "export") == 0)
		export(shell->splited, shell, 1);
	else if (ft_strcmp(shell->splited[0], "unset") == 0)
		unset(shell->splited, shell, 1);
	else if (ft_strcmp(shell->splited[0], "env") == 0)
		env(shell->splited, shell);
	else if (ft_strcmp(shell->splited[0], "exit") == 0)
		free_and_exit(shell->splited, line, shell);
	else
		launch_prog(shell, envp);
	prev_status = g_status;
}

void	pipe_fdout_fdin(t_shell *shell, int fdpipe[2], int i)
{
	dup2(shell->fdin, 0);
	close(shell->fdin);
	if (i == shell->numcommands - 1)
	{
		if (shell->outfile_rule == 1)
			shell->fdout = open(shell->outfile, O_CREAT
					| O_WRONLY | O_TRUNC, 0777);
		else if (shell->outfile_rule == 2)
		{
			printf("ALOOO\n");
			shell->fdout = open(shell->outfile, O_CREAT
					| O_WRONLY | O_APPEND, 0777);
		}
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

void	execute(t_shell *shell, char **env, int i)
{
	int	fdpipe[2];
	int	ret;

	pipe_fdout_fdin(shell, fdpipe, i);
	if (shell->numcommands != 1)
		ret = fork();
	else
		ret = 0;
	if (ret == 0)
	{
		execute_child(shell, env, NULL);
		ft_free_double(shell->splited);
	//	free(shell->quote_rules);
		if (shell->numcommands != 1)
			exit (EXIT_SUCCESS);
	}
	else
		wait(NULL);
}
