/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:29:35 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 00:09:38 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_duplicate_replace(t_shell *shell, t_correct_args *helper)
{
	free(shell->splited[helper->i]);
	shell->splited[helper->i] = ft_strdup(helper->new);
	free(helper->value);
	free(helper->new);
	free(helper->word);
}

void	free_args(char *line, t_shell *shell)
{
	int	i;

	free(shell->quote_rules);
	if (shell->infile != NULL)
		free(shell->infile);
	if (shell->outfile != NULL)
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
