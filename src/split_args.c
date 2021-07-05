/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:43:48 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/05 19:09:56 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		countstring2(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
		if (*s == c)
			j = 0;
		else if (j == 0)
		{
			j = 1;
			i++;
		}
		s++;
	}
	return (i);
}

int		countchar2(char const *s2, char c, int i)
{
	int	lenght;

	lenght = 0;
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

char	**makearray2(t_shell *shell, char const *s, char **p, char c, int l)
{
	int	i;
	int	j;
	int	k;
	int	quotes;

	i = 0;
	j = 0;
	quotes = 0;
	while (s[i] != '\0' && j < l)
	{
		k = 0;
		while (s[i] == c || s[i] == '\"' || s[i] == '\'')
		{
			if (s[i] == '\"')
				quotes = 1;
			if (s[i] == '\'')
				quotes = 2;
			i++;
		}
		p[j] = (char *)malloc(sizeof(char) * countchar2(s, c, i) + 1);
		if (p[j] == NULL)
			return (to_free2((char const **)p, j));
		if (quotes == 1)
		{
			shell->quote_rules[j] = 1;
			while (s[i] != '\0' && s[i] != '\"')
				p[j][k++] = s[i++];
			i++;
			if (s[i] == '\0' && s[i - 1] != '\"')
				return (NULL);
			quotes = 0;
		}
		else if (quotes == 2)
		{
			shell->quote_rules[j] = 2;
			while (s[i] != '\0' && s[i] != '\'')
				p[j][k++] = s[i++];
			i++;
			if (s[i] == '\0' && s[i - 1] != '\'')
				return (NULL);
			quotes = 0;
		}
		else
		{
			shell->quote_rules[j] = 0;
			while (s[i] != '\0' && s[i] != c)
				p[j][k++] = s[i++];
		}
		p[j][k] = '\0';
		j++;
	}
	p[j] = 0;
	return (p);
}

char	**split_args(char const *s, t_shell *shell)
{
	char	**p;
	int		i;
	char	c;

	c = ' ';
	if (s == NULL)
		return (NULL);
	i = countstring2(s, c);
	p = (char **)malloc(sizeof(char *) * (i + 1));
	if (p == NULL)
		return (NULL);
	return (makearray2(shell, s, p, c, i));
}
