/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:19:57 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/13 15:58:39 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	loop_quotes(char const *s)
{
	if (*s == '\"')
	{
		s++;
		while (*s != '\"' && *s != '\0')
			s++;
	}
	if (*s == '\'')
	{
		s++;
		while (*s != '\'' && *s != '\0')
			s++;
	}
}

int	countstring2(char const *s, char c)
{
	int	i;

	i = 1;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == '\"')
		{
			s++;
			while (*s != '\"' && *s != '\0')
				s++;
		}
		if (*s == '\'')
		{
			s++;
			while (*s != '\'' && *s != '\0')
				s++;
		}
		if (*s == c)
			i++;
		if (*s != '\0')
			s++;
	}
	return (i);
}

int	countchar2(t_shell shell, char const *s2, int i)
{
	int		lenght;
	char	c;

	lenght = 0;
	if (shell.quotes == 0)
		c = ' ';
	else if (shell.quotes == 1)
		c = '\'';
	else
		c = '\"';
	while (s2[i] != c && s2[i] != '\0')
	{
		lenght++;
		i++;
	}
	return (lenght);
}

char	**to_free2(char const **p, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)p[j]);
	}
	free(p);
	return (NULL);
}
