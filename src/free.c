/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:58:47 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/21 21:05:07 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args(char *line, t_shell *shell)
{
	int	i;

	if (shell->infile != 0)
		free(shell->infile);
	if (shell->outfile != 0)
		free(shell->outfile);
	if (ft_strlen(line) != 0)
	{
		free(line);
		i = 0;
		while (shell->args[i])
			free(shell->args[i++]);
	}
	free(shell->args);
}

void	free_and_exit(char **args, char *line, t_shell *shell)
{
	int		i;

	i = 0;
	while (args[i])
		free(args[i++]);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strlen(shell->env[i]) == 0)
			break ;
		free(shell->env[i++]);
	}
	free(shell->env);
	free(shell->quote_rules);
	free(line);
	free(args);
	exit(EXIT_SUCCESS);
}

void	ft_free_double(char **s)
{
	int	i;

	i = 0;
	if (!s)
	{
		free(s);
		return ;
	}
	while (s[i])
		free(s[i++]);
	free(s);
}
