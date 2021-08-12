/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/12 10:57:56 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

void	treat_infile(t_shell *shell, char **env)
{
	int		fd;
	char	*line;

	if (shell->rule == 12 || shell->rule == 17 || shell->rule == 13)
	{
		fd = open("../tmp", O_CREAT | O_WRONLY | O_APPEND, 0777);
		while (TRUE)
		{
			line = readline("reading: ");
			if (!line)
			{
				printf("\n");
				break ;
			}
			if (ft_strcmp(line, shell->infile) == 0)
				break ;
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		shell->infile = "../tmp";
	}
	shell->fdin = open(shell->infile, O_RDONLY);
	if (shell->rule == 12 || shell->rule == 17 || shell->rule == 13)
		ft_remove(env);
}

void	run_commands(t_shell shell, char **env)
{
	shell.tmpin = dup(0);
	shell.tmpout = dup(1);
	if (shell.rule == 4 || shell.rule == 5 || shell.rule == 11
		|| shell.rule == 12 || shell.rule == 17 || shell.rule == 13)
		treat_infile(&shell, env);
	else
		shell.fdin = dup(shell.tmpin);
	if (shell.fdin < 0)
	{
		printf("shell: No such file or directory\n");
		return ;
	}
	execute(&shell, env);
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

	if (argc != 1 || argv[1])
		exit(EXIT_FAILURE);
	shell.quote_rules = malloc(sizeof(int) * 1000);
	while (TRUE)
	{
		signal(SIGINT, &sigintHandler);
		signal(SIGQUIT, &sigquitHandler);
		line = readinput();
		shell.outfile = get_outfile(line);
		shell.infile = get_infile(line);
		shell.rule = check_rule(line);
		shell.i = 0;
		while (line[shell.i] && line[shell.i] != '>' && line[shell.i] != '<')
			shell.i++;
		line[shell.i] = '\0';
		shell.args = ft_split(line, '|');
		shell.numcommands = 0;
		while (shell.args[shell.numcommands])
			shell.numcommands++;
		run_commands(shell, envp);
		freeArgs(line, &shell);
	}
}
