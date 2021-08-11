/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/11 09:12:12 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_remove(char **envp)
{
	pid_t	pid;
	char	**args;

	if (envp[0][0] == 'a')
		printf("oi\n");
	args = ft_split("rm ../tmp", ' ');
	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return (NULL);
	}
	else if (pid == 0)
	{
		if (execve("/bin/rm", args, NULL) < 0)
			printf("rm: No such file or directory\n");
		exit(0);
	}
	else
	{
		wait(NULL);
		return (NULL);
	}
	return (NULL);
}

void	execute(t_shell shell, char **env)
{
	int	ret;
	int	i;
	int	fdpipe[2];
	char	*line;

	shell.tmpin = dup(0);
	shell.tmpout = dup(1);
	if (shell.rule == 4 || shell.rule == 5 || shell.rule == 11 || shell.rule == 12 || shell.rule == 17 || shell.rule == 13)
	{
		if (shell.rule == 12 || shell.rule == 17 || shell.rule == 13)
		{
			int fd = open("../tmp", O_CREAT | O_WRONLY | O_APPEND, 0777);
			while (TRUE)
			{
				line = readline("reading: ");
				if (ft_strcmp(line, shell.infile) == 0)
					break ;
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
			}
			shell.infile = "../tmp";
		}
		shell.fdin = open(shell.infile, O_RDONLY);
		if (shell.rule == 12 || shell.rule == 17 || shell.rule == 13)
			ft_remove(env);
	}
	else
		shell.fdin = dup(shell.tmpin);
	if (shell.fdin < 0)
	{
		printf("shell: No such file or directory\n");
		return ;
	}
	i = 0;
	while (i < shell.numcommands)
	{
		dup2(shell.fdin, 0);
		close(shell.fdin);
		if (i == shell.numcommands - 1)
		{
			if (shell.rule == 1 || shell.rule == 13 || shell.rule == 5)
				shell.fdout = open(shell.outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			else if (shell.rule == 7 || shell.rule == 17 || shell.rule == 11)
				shell.fdout = open(shell.outfile, O_CREAT | O_WRONLY | O_APPEND, 0777);
			else
				shell.fdout = dup(shell.tmpout);
		}
		else
		{
			pipe(fdpipe);
			shell.fdout = fdpipe[1];
			shell.fdin = fdpipe[0];
		}
		dup2(shell.fdout, 1);
		close(shell.fdout);
		if (shell.numcommands != 1)
			ret = fork();
		else
			ret = 0;
		if (ret == 0)
		{
			shell.splited = split_args(shell.args[i], &shell);
			execute_child(&shell, env, NULL);
			free(shell.splited);
			if (shell.numcommands != 1)
				exit (EXIT_SUCCESS);
		}
		else
			wait(NULL);
		i++;
	}
	dup2(shell.tmpin, 0);
	dup2(shell.tmpout, 1);
	close(shell.tmpin);
	close(shell.tmpout);
	wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;
	int		i;

	if (argc != 1 || argv[1])
		exit(EXIT_FAILURE);
	shell.quote_rules = malloc(sizeof(int) * 1000);
	while (TRUE)
	{
		signal(SIGINT, sigintHandler);
		signal(SIGQUIT, sigquitHandler);
		line = readinput();
		shell.outfile = get_outfile(line);
		shell.infile = get_infile(line);
		shell.rule = check_rule(line);
		i = 0;
		while (line[i] && line[i] != '>' && line[i] != '<')
			i++;
		line[i] = '\0';
		shell.args = ft_split(line, '|');
		i = 0;
		while (shell.args[i])
			i++;
		shell.numcommands = i;
		execute(shell, envp);
		freeArgs(line, &shell);
	}
	exit (EXIT_SUCCESS);
}
