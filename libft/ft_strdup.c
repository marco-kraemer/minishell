/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:00:39 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/11 09:10:56 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	size_t	length;
	char	*p;
	char	*k;

	k = (char *)s;
	length = ft_strlen(k) + 1;
	p = malloc(length);
	if (!p)
		return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = k[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
