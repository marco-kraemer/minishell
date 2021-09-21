/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/20 22:45:55 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

void	infile_loop(t_shell *shell, int fd)
{
	char	*line;

	while (TRUE)
	{
		line = readline("reading: ");
		if (!line)
		{
			printf("\n");
			break ;
		}
		if (ft_strcmp(line, shell->infile) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	treat_infile(t_shell *shell)
{
	int		fd;

	if (shell->rule == 12 || shell->rule == 17 || shell->rule == 13)
	{
		fd = open("../tmp", O_CREAT | O_WRONLY | O_APPEND, 0777);
		infile_loop(shell, fd);
		free(shell->infile);
		shell->infile = ft_strdup("../tmp");
	}
	shell->fdin = open(shell->infile, O_RDONLY);
	if (shell->rule == 12 || shell->rule == 17 || shell->rule == 13)
		ft_remove();
}

void	run_commands(t_shell *shell, char **env)
{
	shell->tmpin = dup(0);
	shell->tmpout = dup(1);
	if (shell->rule == 4 || shell->rule == 5 || shell->rule == 11
		|| shell->rule == 12 || shell->rule == 17 || shell->rule == 13)
		treat_infile(shell);
	else
		shell->fdin = dup(shell->tmpin);
	if (shell->fdin < 0)
	{
		printf("shell: No such file or directory\n");
		return ;
	}
	execute(shell, env);
	dup2(shell->tmpin, 0);
	dup2(shell->tmpout, 1);
	close(shell->tmpin);
	close(shell->tmpout);
	wait(NULL);
}

void	init_env(char **envp, t_shell *shell)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	shell->env = (char **)malloc(sizeof(char *) * (i + 10000));
	i = 0;
	while (envp[i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->env[i] = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	if (argc != 1 || argv[1])
		exit(EXIT_FAILURE);
	init_env(envp, &shell);
	while (TRUE)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, &sigquit_handler);
		line = readinput(&shell);
		shell.outfile = get_outfile(line);
		shell.infile = get_infile(line);
		shell.rule = check_rule(line);
		shell.i = 0;
		while (line[shell.i] && line[shell.i] != '>' && line[shell.i] != '<')
			shell.i = treat_quotes(line, shell.i);
		line[shell.i] = '\0';
		shell.args = ft_split(line, '|'); // ALTERAR
		shell.numcommands = 0;
		while (shell.args[shell.numcommands])
			shell.numcommands++;
		run_commands(&shell, envp);
		free_args(line, &shell);
	}
}
