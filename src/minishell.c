/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/30 14:03:54 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execArgsPiped(char **tmp, char **env)
{
	// 0 is read end, 1 is write end
	int pipefd[2]; 
	pid_t p1, p2;

	signal(SIGINT, sigintHandler_process);
	pipe(pipefd);
	p1 = fork();
	if (p1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execute(ft_split(tmp[0], ' '), env, NULL, 1);
	}
	else
	{
		p2 = fork();
		if (p2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			execute(ft_split(tmp[1], ' '), env, NULL, 1);
			close(pipefd[0]);
		}
		else
		{
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
			execArgsPiped(tmp, envp);
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
