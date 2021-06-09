/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:07 by user42            #+#    #+#             */
/*   Updated: 2021/06/09 14:45:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_line(void)
{
	int		bufsize;
	int		position;
	int		c;
	char	buf[1];
	char	*buffer;

	bufsize = BUFF_SIZE;
	position = 0;
	buffer = malloc(sizeof(char) * bufsize);
	if (!buffer)
	{
		printf("Allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (TRUE)
	{
		c = read(0, buf, 1);
	//	printf("%c\n", buf[0]);
		if (buf[0] == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		buffer[position] = buf[0];
		position++;
	}
}

int	launch_program(char **args)
{
	int	pid;
	int	wpid;
	int	status;

	pid = fork(); // Creating child and parent process
	//Treat child, replacing it with a new process 
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("shell");
		exit(EXIT_SUCCESS);
	} 
	// Check error (fork < 0)
	if (pid < 0)
		perror("shell");
	// Treat parent
	else if (pid != 0)
	{
		while (TRUE)
		{
			wpid = waitpid(pid, &status, WUNTRACED); // WUNTRACED = child processes specified by pid that are stopped
			if (!WIFEXITED(status) && !WIFSIGNALED(status))
				break ;
		}
	}
	return (1);
}

int	execute(char **args, char **envp, char *line)
{
	if (args[0] == NULL)
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (change_directory(args));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (export(args, envp));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset(args, envp));
	else if (ft_strcmp(args[0], "env") == 0)
		return (env(args, envp));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (free_and_exit(args, line));
	else if (ft_strcmp(args[0], "^C") == 0)
		printf("OI\n");
	else
		printf("%s: command not found\n", args[0]);
	return (1);
	//return (launch_program(args));
}