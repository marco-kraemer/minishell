/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_tabs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 23:50:43 by user42            #+#    #+#             */
/*   Updated: 2021/09/28 14:54:24 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	treat_quotes2(char *s, int i)
{
	if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'')
		{
			i++;
		}
	}
	else if (s[i] == '\"')
	{
		i++;
		while (s[i] != '\"')
		{
			i++;
		}
	}
	i++;
	return (i);
}

char	**treat_tabs(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == 9)
				args[i][j] = 32;
			j = treat_quotes2(args[i], j);
		}
		i++;
	}
	return (args);
}
