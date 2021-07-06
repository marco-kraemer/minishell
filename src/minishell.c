/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 12:20:36 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_shell shell, char **env)
{
	int	ret;
	int	i;
	int	fdpipe[2];

	shell.tmpin = dup(0);
	shell.tmpout = dup(1);
	shell.fdin = dup(shell.tmpin);
	i = 0;
	while (i < shell.numcommands)
	{
		dup2(shell.fdin, 0);
		close(shell.fdin);
		if (i == shell.numcommands - 1)
		{
			if (shell.rule == 1 || shell.rule == 13)
				shell.fdout = open(shell.outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			else if (shell.rule == 7 || shell.rule == 17)
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
				exit (1);
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
		//shell.infile = get_infile(line);
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
