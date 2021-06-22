/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/22 12:39:39 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execArgsPiped(char **parsed, char **parsedpipe, char **env)
{
	// 0 is read end, 1 is write end
	int pipefd[2]; 
	pid_t p1, p2;

	if (pipe(pipefd) < 0)
	{
		printf("\nPipe could not be initialized");
		return;
	}
	p1 = fork();
	if (p1 < 0)
	{
		printf("\nCould not fork");
		return;
	}
	if (p1 == 0)
	{
		// Child 1 executing..
		// It only needs to write at the write end
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (execute(parsed, env, NULL, 1) < 0)
		{
			printf("Could not execute command 2..\n");
			exit(0);
		}

	}
	else
	{
		// Parent executing
		p2 = fork();
		if (p2 < 0)
		{
			printf("\nCould not fork");
			return;
		}
		// Child 2 executing..
		// It only needs to read at the read end
		if (p2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execute(parsedpipe, env, NULL, 1) < 0)
			{
				printf("Could not execute command 2..\n");
				exit(0);
			}
		}
		else
		{
			// parent executing, waiting for two children
			wait(NULL);
			wait(NULL);
		}
	}
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
	char	**parsedArgs;
	char	**parsedArgsPiped;
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
		parsedArgs = ft_split(tmp[0], ' '); // From beginning to '|' or '\0;
		parsedArgsPiped = ft_split(tmp[1], ' '); // From '|' to end;
		if (flag == 0)
			value = execute(parsedArgs, envp, line, 0);
		else if (flag == 1)
			execArgsPiped(parsedArgs, parsedArgsPiped, envp);
		if (value != NULL)
			printf("%s\n", value);
		

		// FREE
		if (line)
		{
			free(line);
			i = 0;
			while (parsedArgs[i])
				free(parsedArgs[i++]);
			free(parsedArgs);
			i = 0;
			while (tmp[i])
				free(tmp[i++]);
			free(tmp);
		}
		if (parsedArgsPiped)
		{
			i = 0;
			while (parsedArgsPiped[i])
				free(parsedArgsPiped[i++]);
			free(parsedArgsPiped);
		}
	}
	exit (EXIT_SUCCESS);
}
