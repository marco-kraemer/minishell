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

int	launch_program()
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

int	pwd()
{
	char	cwd[FILENAME_MAX];
	int	i;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	i = 0;
	while (cwd[i])
		write (1, &cwd[i++], 1);
	write (1, "\n", 1);
	return (1);
}

int	export(char **args, char **env)
{
	int		i;
	int		j;
	char	name[FILENAME_MAX];
	char	value[FILENAME_MAX];

	i = 0;
	while (args[i])
		i++;
	if (i == 1) // LIST VARIABLES
	{	
		i = 0;
		while (env[i + 1])
			printf("declare -x %s\n", env[i++]);
	}
	else // ADD / CHANGE VARIABLES
	{
		i = 0;
		// GET VARIABLE VALUE
		while (args[1][i] != '=')
			i++;
		i++;
		j = 0;
		while (args[1][i])
			value[j++] = args[1][i++];
		value[j++] = '\0';
		// GET VARIABLE NAME
		i = 0;
		j = 0;
		while (args[1][i] != '=')
			name[j++] = args[1][i++];
		// CHANGE VARIABLE VALUE
		i = 0;
		while (env[i])
		{
			if (ft_strncmp(name, env[i], ft_strlen(name)) == 0)
			{
				int k = 0;
				j = 0;
				while (env[i][j] != '=')
					j++;
				j++;
				while (value[k])
					env[i][j++] = value[k++];
				env[i][j++] = '\0';
				return (1);
			}
			i++;
		}
		// ADD VARIABLES
		// TODO
	}
	return (1);
}

char	**delete_line(char **env, int line)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = env;
	while (env[i + j])
	{
		if (i == line)
			j = 1;
		new[i] = env[i + j];
		i++;
	}
	i = 0;
	env = new;
	return (env);
}

int	unset(char **args, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*name;
	char	*variable;

	// GET VARIABLE NAME
	i = 0;
	j = 0;
	name = malloc(sizeof(char) * ft_strlen(args[1]));
	while (args[1][i] != '\0')
		*(name + j++) = args[1][i++];
	name[j + 1] = '\0';
	i = 0;
	while (name[i])
	{
		if (name[i] == '=')
		{
			printf("unset: %s: not a valid identifier\n", name);
			return (0);
		}
		i++;
	}
	// FIND VARIABLE IN ENV
	variable = getenv(name);
	if (variable == NULL)
	{
		printf("\n");
		return (0);
	}
	// DELETE VARIABLE
	i = 0;
	k = 0;
	variable = malloc(sizeof(char) * ft_strlen(args[1]));
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j])
		{
			variable[j] = env[i][j];
			j++;
		}
		variable[j] = '\0';
		if (ft_strcmp(name, variable) == 0)
		{
			env = delete_line(env, i);
		}
		i++;
	}
	free(name);
	free(variable);
	return (1);
}

int	execute(char **args, char **envp)
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
	else
		printf("%s: command not found\n", args[0]);
	return (launch_program());
}

char	**get_variable_list(char **env)
{
	int		i;
	char	**new;

	i = 0;
	while (env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (env[i])
	{
		new[i] = malloc(sizeof(char) * ft_strlen(env[i]));
		i++;
	}
	new[i] = malloc(1);
	new[i] = "\0";
	i = 0;
	while (env[i])
	{
		new[i] = env[i];
		i++;
	}
	return (new);
}

int	main(int argc, char **argv, char **envp)
{
	char	cwd[FILENAME_MAX];
	char	*line;
	char	**args;
	char	**env;
	int		status;
	int		i;

	env = get_variable_list(envp);
	while (TRUE)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		i = 0;
		write(1, "\033[0;36m", ft_strlen("\033[0;36m")); // CYAN
		while (cwd[i])
		{
			write (1, &cwd[i++], 1);
		}
		write(1, "\033[0m", ft_strlen("\033[0m"));
		write(1, "$ ", 2);
		line = read_line();
		args = ft_split(line, ' ');
		status = execute(args, env);
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
