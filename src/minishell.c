/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/22 09:02:19 by maraurel         ###   ########.fr       */
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
		if (execute(parsed, env, NULL) < 0)
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
			if (execute(parsedpipe, env, NULL) < 0)
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

char	*readinput()
{
	char	cwd[FILENAME_MAX];
	char	*line;
	int		i;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		strerror(3);
	line = readline("\033[0;36m minishell$ \033[0;37m");
	if (ft_strlen(line) != 0)
		add_history(line);
	return (line);
}

void	sigintHandler(int sig_num)
{
	if (!sig_num)
		return;
	printf("\n");
	readinput();
}

void	launch(char **parsed, char **envp)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return;
	}
	else if (pid == 0) 
	{
		if (ft_strlen(envp[0]) == 3535)
			printf("oi\n");
		if (execve(parsed[0], parsed, envp) < 0)
			printf("%s: No such file or directory\n", parsed[0]);
		exit(0);
	}
	else
	{
		wait(NULL); 
		return;
	}
}

int	checkFlag(char *line)
{
	char	**s;
	int		i;
	
	if (ft_strlen(line) == 0)
		return (3);
	if (ft_strncmp("env ", line, 4) == 0
	|| ft_strncmp("export ", line, 7) == 0
	|| ft_strncmp("cd ", line, 3) == 0
	|| ft_strncmp("exit", line, 4) == 0
	|| ft_strncmp("unset ", line, 6) == 0
	|| ft_strncmp("./", line, 2) == 0
	|| ft_strncmp("echo ", line, 5) == 0)
		return (1);
	s = ft_split(line, '|');
	i = 0;
	while (s[i])
		i++;
	if (i > 1)
		return (2);
	return (0);
}

void	exec_bultin(char **parsed, char **env)
{
	parsed[0] = ft_strjoin("/bin/", parsed[0]);
	launch(parsed, env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**env;
	char	**parsedArgs;
	char	**parsedArgsPiped;
	char	**tmp;
	int		flag;
	char	*value;
	int		i;

	env = get_variable_list(envp);
	if (argc == 54225 && argv)
		printf("oi\n");
	flag = 0;
	while (TRUE)
	{
		signal(SIGINT, sigintHandler);
		line = readinput();
		i = 0;
		value = NULL;
		flag = checkFlag(line); // 0 if executable or builtin, 1 if command, 2 if including pipe;
		tmp = ft_split(line, '|');
		parsedArgs = ft_split(tmp[0], ' '); // From beginning to '|' or '\0;
		parsedArgsPiped = ft_split(tmp[1], ' '); // From '|' to end;
		if (flag == 0)
			exec_bultin(parsedArgs, env);
		else if (flag == 1)
			value = execute(parsedArgs, env, line);
		else if (flag == 2)
			execArgsPiped(parsedArgs, parsedArgsPiped, env);
		if (value != NULL)
			printf("%s\n", value);
	}
	exit (EXIT_SUCCESS);
}
