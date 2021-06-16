/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:07 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/16 15:21:57 by maraurel         ###   ########.fr       */
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

char	*launch_program(char **args)
{
	int	pid;
	int	wpid;
	int	status;

	status = 0;
	pid = fork(); // Creating child and parent process
	//Treat child, replacing it with a new process 
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1) // CHANGE LATER (NOT ALLOWED FUNCTION)
			printf("shell: No such file or directory\n");
		exit(EXIT_FAILURE);
	} 
	// Check error (fork < 0)
	else if (pid < 0)
	{
		printf("%s: command not found\n", args[0]);
		strerror(3);
	}
	// Treat parent
	else
	{
		wpid = 1;
		while (wpid >= 0)
		{
			wpid = waitpid(pid, &status, WUNTRACED); // WUNTRACED = child processes specified by pid that are stopped
		}
	}
	return (NULL);
}

char	*execute(char **args, char **envp, char *line)
{
	char	*ret;

	ret = NULL;
	if (args[0] == NULL)
		return (NULL);
	if (ft_strcmp(args[0], "cd") == 0)
		return (change_directory(args));
	else if (ft_strcmp(args[0], "echo") == 0)
		ret = (echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (export(args, envp));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset(args, envp));
	else if (ft_strcmp(args[0], "env") == 0)
		return (env(args, envp));
	else if (ft_strcmp(args[0], "exit") == 0)
		free_and_exit(args, line);
	else if (ft_strncmp(args[0], "./", 2) == 0)
		return (launch_program(args));
	if (ret == NULL)
	{
		printf("%s: command not found\n", args[0]);
		return (NULL);
	}
	check_redirection(args, ret);
	return (ret);
}
