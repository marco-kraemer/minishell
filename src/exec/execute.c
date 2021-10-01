/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:07 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 21:29:53 by maraurel         ###   ########.fr       */
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
	path_args = find_path_value(shell);
	if (!ft_strcmp(shell->splited[0], "./")
		|| !ft_strcmp(shell->splited[0], "../"))
	{
		g_status = 126;
		printf("%s: Is a directory\n", shell->splited[0]);
	}
	else if (ft_strncmp(shell->splited[0], "./", 2) == 0
		|| ft_strncmp(shell->splited[0], "../", 3) == 0)
		launch(shell, envp, path_args, "minishell: No such file or directory");
	else
		launch(shell, envp, path_args, "command not found");
	if (path_args)
	{
		while (path_args[i])
			free(path_args[i++]);
		free(path_args);
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

void	execute(t_shell *shell, char **env, int i)
{
	int	fdpipe[2];
	int	ret;

	dup2(shell->fdin, 0);
	close(shell->fdin);
	pipe_fdout_fdin(shell, fdpipe, i);
	if (shell->numcommands != 1)
		ret = fork();
	else
		ret = 0;
	if (ret == 0)
	{
		execute_child(shell, env, NULL);
		if (shell->numcommands != 1)
			exit (EXIT_SUCCESS);
	}
	else
		wait(NULL);
}

void	parse_execute(t_shell *shell, char **env, int i)
{
	shell->infile = NULL;
	shell->outfile = NULL;
	shell->tmpin = dup(0);
	shell->tmpout = dup(1);
	while (i < shell->numcommands)
	{
		shell->splited = split_args(shell->args[i], shell);
		if (shell->splited != NULL)
		{
			shell->splited = expander(shell, g_status, shell->env);
			shell->splited = get_in_and_out_file(shell, shell->splited);
			if (treat_infile(shell, i) == 0)
				execute(shell, env, i);
			ft_free_double_int(shell->quote_rules_char);
			free(shell->infile);
			free(shell->outfile);
		}
		free(shell->quote_rules);
		ft_free_double(shell->splited);
		i++;
	}
	reset_tmpin_tmpout(shell);
	wait(NULL);
}
