/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/02 09:32:21 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_outfile(char *line)
{
	char	*ret;
	int		i;

	i = 0;
	while(line[i] != '>' && line[i])
		i++;
	if ((int)ft_strlen(line) == i)
		return (NULL);
	i++;
	if (line[i] == '>')
		i++;
	while (line[i] == ' ')
		i++;
	ret = ft_substr(line, i, ft_strlen(line) - i);
	return (ret);
}

void	executeArgs(char **tmp, char **env, char *outfile, int numCommands, int rule)
{
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	ret;
	int	fdout;
	int	i;
	int	fdpipe[2];
	char	**splited;

	tmpin = dup(0);
	tmpout = dup(1);
	fdin = dup(tmpin);
	i = 0;
	while (i < numCommands)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == numCommands - 1)
		{
			if (rule == 1 || rule == 13)
				fdout = open(outfile, O_CREAT | O_WRONLY |O_TRUNC, 0777);
			else if (rule == 7 || rule == 17)
				fdout = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0777);
			else
				fdout = dup(tmpout);
		}
		else
		{
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		if (numCommands != 1)
			ret = fork();
		else
			ret = 0;
		if (ret == 0)
		{
			splited = ft_split(tmp[i], ' ');
			execute(splited, env, NULL);
			free(splited);
			if (numCommands != 1)
				exit (1);
		}
		else
			wait(NULL);
		i++;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	wait(NULL);
}

int	check_rule(char *line)
{
	int	i;
	int	ret;
	int	check1;
	int	check2;

	i = 0;
	ret = 0;
	check1 = 0;
	check2 = 0;
	while (line[i])
	{
		if (line[i] == '>' && check1 == 0)
		{
			ret += 1;
			check1++;
			if (line[i + 1] == '>')
				ret += 6;
		}
		if (line[i] == '<' && check2 == 0)
		{
			ret += 4;
			check2++;
			if (line[i + 1] == '<')
				ret += 6;
		}
		i++;
	}
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*outfile;
//	char	*infile	
	char	**args;
	int		i;
	int		rule;

	if (argc == 54225 && argv)
		printf("oi\n");
	while (TRUE)
	{
		signal(SIGINT, sigintHandler);
		signal(SIGQUIT, sigquitHandler);
		line = readinput();
		outfile = get_outfile(line);
		//infile = get_infile(line);
		rule = check_rule(line);
		i = 0;
		while (line[i] && line[i] != '>' && line[i] != '<')
			i++;
		line[i] = '\0';
		args = ft_split(line, '|');
		i = 0;
		while (args[i])
			i++;
		executeArgs(args, envp, outfile, i, rule);
	
		// FREE
		if (ft_strlen(line) != 0)
		{
			free(line);
			i = 0;
			while (args[i])
				free(args[i++]);
			free(args);
		}
	}
	exit (EXIT_SUCCESS);
}
