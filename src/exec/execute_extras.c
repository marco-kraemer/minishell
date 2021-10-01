/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_extras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:36:36 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 21:30:09 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_fdout_fdin(t_shell *shell, int fdpipe[2], int i)
{
	if (shell->outfile_rule == 1)
		shell->fdout = open(shell->outfile, O_CREAT
				| O_WRONLY | O_TRUNC, 0777);
	else if (shell->outfile_rule == 2)
		shell->fdout = open(shell->outfile, O_CREAT
				| O_WRONLY | O_APPEND, 0777);
	else if (i == shell->numcommands - 1)
		shell->fdout = dup(shell->tmpout);
	else
	{
		pipe(fdpipe);
		shell->fdout = fdpipe[1];
		shell->fdin = fdpipe[0];
	}
	dup2(shell->fdout, 1);
	close(shell->fdout);
}

void	reset_tmpin_tmpout(t_shell *shell)
{
	dup2(shell->tmpin, 0);
	dup2(shell->tmpout, 1);
	close(shell->tmpin);
	close(shell->tmpout);
}

void	infile_loop(t_shell *shell, int fd)
{
	char	*line;

	while (TRUE)
	{
		line = readline("reading: ");
		if (!line)
		{
			printf("\n");
			break ;
		}
		if (ft_strcmp(line, shell->infile) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	treat_infile(t_shell *shell, int i)
{
	int		fd;

	if (shell->infile_rule == 2)
	{
		fd = open("../tmp", O_CREAT | O_WRONLY | O_APPEND, 0777);
		infile_loop(shell, fd);
		free(shell->infile);
		shell->infile = ft_strdup("../tmp");
	}
	if (shell->infile_rule == 1 || shell->infile_rule == 2)
		shell->fdin = open(shell->infile, O_RDONLY);
	else if (i == 0)
		shell->fdin = dup(shell->tmpin);
	if (shell->fdin < 0)
	{
		printf("minishell: %s: No such file or directory\n", shell->infile);
		return (1);
	}
	if (shell->infile_rule == 2)
		ft_remove();
	return (0);
}
