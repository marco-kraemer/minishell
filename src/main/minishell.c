/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:12:29 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 10:38:01 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_status;

void	init_env(char **envp, t_shell *shell)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	shell->env = (char **)malloc(sizeof(char *) * (i + 10000));
	i = 0;
	while (envp[i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->env[i] = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	if (argc != 1 || argv[1])
		exit(EXIT_FAILURE);
	init_env(envp, &shell);
	while (TRUE)
	{
		line = readinput(&shell);
		shell.i = 0;
		line = parse_line(line);
		shell.args = split_commands(line);
		shell.args = treat_tabs(shell.args);
		shell.numcommands = 0;
		if (shell.args)
		{
			while (shell.args[shell.numcommands])
				shell.numcommands++;
			parse_execute(&shell, envp, 0);
		}
		free_args(line, &shell);
	}
}
