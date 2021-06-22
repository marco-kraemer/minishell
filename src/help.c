/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:35:21 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/22 11:47:37 by maraurel         ###   ########.fr       */
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

void	sigintHandler(int sig_num)
{
	if (!sig_num)
		return;
	printf("\n");
	readinput();
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
