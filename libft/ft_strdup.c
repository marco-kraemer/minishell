/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:00:39 by maraurel          #+#    #+#             */
/*   Updated: 2021/02/10 18:08:12 by maraurel         ###   ########.fr       */
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
	if (!(p = malloc(length)))
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
