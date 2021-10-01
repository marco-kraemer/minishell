/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:29:35 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 21:46:17 by maraurel         ###   ########.fr       */
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
	if (ft_strlen(line) != 0)
		free(line);
	ft_free_double(shell->args);
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

void	ft_free_double_int(int **s)
{
	int	i;

	if (!s[0])
	{
		free(s);
		return ;
	}
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
		if (s[i][0] == 0)
			break ;
	}
	free(s[i]);
	free(s);
}
