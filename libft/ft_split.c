/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:43:48 by maraurel          #+#    #+#             */
/*   Updated: 2021/02/16 01:39:14 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		countstring(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
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

int		countchar(char const *s2, char c, int i)
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

char	**to_free(char const **p, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)p[j]);
	}
	free(p);
	return (NULL);
}

char	**makearray(char const *s, char **p, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		p[j] = (char *)malloc(sizeof(char) * countchar(s, c, i) + 1);
		if (p[j] == NULL)
			return (to_free((char const **)p, j));
		while (s[i] != '\0' && s[i] != c)
			p[j][k++] = s[i++];
		p[j][k] = '\0';
		j++;
	}
	p[j] = 0;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		i;

	if (s == NULL)
		return (NULL);
	i = countstring(s, c);
	p = (char **)malloc(sizeof(char *) * (i + 1));
	if (p == NULL)
		return (NULL);
	return (makearray(s, p, c, i));
}
