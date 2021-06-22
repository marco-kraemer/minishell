/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:07 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/21 22:20:45 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ret = pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		ret = export(args, envp);
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset(args, envp));
	else if (ft_strcmp(args[0], "env") == 0)
		ret  = env(args, envp);
	else if (ft_strcmp(args[0], "exit") == 0)
		free_and_exit(args, line);
	else if (ft_strncmp(args[0], "./", 2) == 0)
	{
		launch(args, envp);
		return (NULL);
	}
	else
	{
		launch(args, envp);
		//printf("%s: command not found\n", args[0]);
		return (NULL);
	}
	check_redirection(args, ret);
	return (ret);
}
