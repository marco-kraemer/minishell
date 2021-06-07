/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/01 16:26:35 by maraurel         ###   ########.fr       */
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

int	launch_program(char **args, char  **envp)
{
	int	pid;
	int	wpid;
	int	status;

	pid = fork(); // Creating child and parent process
	//Treat child, replacing it with a new process 
//	if (pid == 0)
//	{
//		if (execve(args[0], args, envp) == -1) 
//			perror("shell");
//		exit(EXIT_SUCCESS);
//	} 
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

int	change_directory(char **args)
{
	if (args[1] == NULL)
		chdir("");
	else
	{
		if (chdir(args[1]) != 0)
			perror("shell");
	}
	return (1);
}

int	echo(char **args)
{
	int	i;

	i = 1;
	if (ft_strcmp(args[1], "-n") == 0)
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i++], 1);
		if (args[i])
			write (1, " ", 1);
	}
	if (ft_strcmp(args[1], "-n") != 0)
		printf("\n");
	return (1);
}

int	execute(char **args, char **envp)
{
	int		i;

	if (args[0] == NULL)
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (change_directory(args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo(args));
	else
		printf("%s: command not found\n", args[0]);
	return (launch_program(args, envp));
}

int	main(int argc, char **argv, char **envp)
{
	char	cwd[FILENAME_MAX];
	char	*line;
	char	**args;
	int		status;
	int		i;

	while (TRUE)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		i = 0;
		while (cwd[i])
			write (1, &cwd[i++], 1);
		write(1, "$ ", 2);
		line = read_line();
		args = ft_split(line, ' ');
		status = execute(args, envp);
		if (ft_strcmp(args[0], "exit") == 0)
		{
			i = 0;
			while (args[i])
				free(args[i++]);
			free(line);
			free(args);
			exit(EXIT_SUCCESS);
		}
		i = 0;
		while (args[i])
			free(args[i++]);
		free(line);
		free(args);
	}
	exit (EXIT_SUCCESS);
}
