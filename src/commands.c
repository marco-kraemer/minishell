/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <maraurel@student.42sp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:10 by user42            #+#    #+#             */
/*   Updated: 2021/06/14 08:04:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_directory(char **args)
{
	if (args[1] == NULL)
		chdir("");
	else
	{
		if (chdir(args[1]) != 0)
			printf("shell: No such file or directory\n");
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
		printf("getcwd() error\n");
	i = 0;
	while (cwd[i])
		write (1, &cwd[i++], 1);
	write (1, "\n", 1);
	return (1);
}

int	env(char **args, char **env)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i == 1) // LIST VARIABLES
	{	
		i = 0;
		while (env[i + 1])
			printf("%s\n", env[i++]);
	}
	else
		printf("env: invalid number of arguments");
	return (1);
}
