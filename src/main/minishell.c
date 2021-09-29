/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/29 17:05:20 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	if (shell->infile_rule == 2)
	{
		fd = open("../tmp", O_CREAT | O_WRONLY | O_APPEND, 0777);
		infile_loop(shell, fd);
		free(shell->infile);
		shell->infile = ft_strdup("../tmp");
	}
	if (shell->infile_rule == 1 || shell->infile_rule == 2)
		shell->fdin = open(shell->infile, O_RDONLY);
	else
		shell->fdin = dup(shell->tmpin);
	if (shell->fdin < 0)
	{
		printf("shell: No such file or directory\n");
		return ;
	}
	if (shell->infile_rule == 2)
		ft_remove();
}

void	parse_execute(t_shell *shell, char **env)
{
	int	i;

	i = 0;
	while (i < shell->numcommands)
	{
		shell->splited = split_args(shell->args[i], shell);
		if (shell->splited)
		{
			shell->splited = tokenizer(shell, g_status, shell->env);
			shell->splited = get_in_and_out_file(shell, shell->splited);
			shell->tmpin = dup(0);
			shell->tmpout = dup(1);
			treat_infile(shell);
			execute(shell, env, i);
			dup2(shell->tmpin, 0);
			dup2(shell->tmpout, 1);
			close(shell->tmpin);
			close(shell->tmpout);
		}
		i++;
	}
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

/* Inserir espaços antes e depois de redirecionadores*/
char	*parse_line(char *line)
{
	int	i;
	int	extra;
	char	*new;

	i = 0;
	extra = 0;
	while (line[i])
	{
		if (line[i] == '>')
		{
			extra += 2;
			i++;
			while (line[i] == '>')
				i++;
		}
		if (line[i] == '<')
		{
			extra += 2;
			i++;
			while (line[i] == '<')
				i++;
		}
		else
			i = treat_quotes(line, i);
	}

	new = (char *) malloc(sizeof(char) * (ft_strlen(line) + extra) + 1);

	int	j;
	j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			new[j++] = line[i++];
			while (line[i] && line[i] != '\"')
				new[j++] = line[i++];
			new[j++] = line[i++];
		}
		else if (line[i] == '\'')
		{
			new[j++] = line[i++];
			while (line[i] && line[i] != '\'')
				new[j++] = line[i++];
			new[j++] = line[i++];
		}
		else if (line[i] == '<')
		{
			new[j++] = ' ';
			while (line[i] == '<')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else if (line[i] == '>')
		{
			new[j++] = ' ';
			while (line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
		{
			new[j] = line[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	free(line);
	return (new);
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
		line = readinput(&shell);
		shell.i = 0;
		line = parse_line(line);
		shell.args = split_commands(line);
		shell.args = treat_tabs(shell.args);
		shell.numcommands = 0;
		while (shell.args[shell.numcommands])
			shell.numcommands++;
		parse_execute(&shell, envp);
		free_args(line, &shell);
	}
}
