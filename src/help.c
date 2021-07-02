/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:35:21 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/02 09:36:43 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	free_and_exit(char **args, char *line)
{
	int		i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(line);
	free(args);
	exit(EXIT_SUCCESS);
}

void	sigintHandler_process(int sig_num)
{
	if (sig_num != SIGINT)
		return;
	printf("\n");
	signal(SIGINT, sigintHandler_process);
}

void	sigintHandler(int sig_num)
{
	if (sig_num != SIGINT)
		return;
	printf("\n");
	ft_putstr_fd(PROMPT_MSG, 1);
	signal(SIGINT, sigintHandler);
}

void	sigquitHandler(int sig_num)
{
	if (sig_num != SIGQUIT)
		return;
//	printf("\n");
//	ft_putstr_fd(PROMPT_MSG, 1);
	signal(SIGQUIT, sigquitHandler);
}

char	*readinput()
{
	char	*line;
	int		i;

	i = 0;
	line = readline(PROMPT_MSG);
	if (!line)
	{
		printf("exit\n");
		exit (0);
	}
	if (ft_strlen(line) != 0)
		add_history(line);
	return (line);
}
