/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/21 14:35:43 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

// Function where the system command is executed
void execArgs(char** parsed, char **envp)
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
		if (execve(parsed[0], parsed, envp) < 0)
			printf("%s: No such file or directory\n", parsed[0]);
		exit(0);
	}
	else
	{
		// waiting for child to terminate
		wait(NULL); 
		return;
	}
}

int	checkFlag(char *line)
{
	if (ft_strlen(line) == 0)
		return (0);
	else if (ft_strncmp(line, "./", 2) == 0)
		return (2);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**env;
	char	**parsedArgs;
	int		flag;

	env = get_variable_list(envp);
	if (argc == 54225 && argv)
		printf("oi\n");
	flag = 0;
	while (TRUE)
	{
		signal(SIGINT, sigintHandler);
		line = readinput();
		flag = checkFlag(line); // 0 if nothing, 1 if command, 2 if binary, 3 if including pipe;
		parsedArgs = ft_split(line, ' ');
		if (flag == 2)
			execArgs(parsedArgs, envp);
	}
	exit (EXIT_SUCCESS);
}
