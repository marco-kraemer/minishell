/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/30 14:50:44 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execArgsPiped(char **tmp, char **env, int numCommands)
{
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	ret;
	int	fdout;
	int	i;
	int	fdpipe[2];

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
		ret = fork();
		if (ret == 0)
		{
			execute(ft_split(tmp[i], ' '), env, NULL, 0);
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

int	checkFlag(char *line)
{
	char	**s;
	int		i;
	
	if (ft_strlen(line) == 0)
		return (2);
	i = 0;
	s = ft_split(line, '|');
	while (s[i])
		i++;
	if (i > 1)
		return (1);
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**tmp;
	int		flag;
	int		i;
	char	*value;

	if (argc == 54225 && argv)
		printf("oi\n");
	flag = 0;
	while (TRUE)
	{
		signal(SIGINT, sigintHandler);
		line = readinput();
		i = 0;
		value = NULL;
		flag = checkFlag(line); // 0 builtin, simple command or binary, 1 if including pipe;
		tmp = ft_split(line, '|');
		if (flag == 0)
			value = execute(ft_split(tmp[0], ' '), envp, line, 0);
		else if (flag == 1)
		{
			i = 0;
			while (tmp[i])
				i++;
			execArgsPiped(tmp, envp, i);
		}
		if (value != NULL)
			printf("%s\n", value);
		

		// FREE
		if (ft_strlen(line) != 0)
		{
			free(line);
			i = 0;
			while (tmp[i])
				free(tmp[i++]);
			free(tmp);
		}
	}
	exit (EXIT_SUCCESS);
}
