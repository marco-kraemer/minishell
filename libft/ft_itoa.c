/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:02:09 by maraurel          #+#    #+#             */
/*   Updated: 2021/02/12 19:34:08 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_digits(int n)
{
	int		i;

	if (n == -2147483648)
		return (10);
	i = 1;
	if (n < 0)
		n = n * (-1);
	while (i > 0)
	{
		n = n / 10;
		if (n < 1)
			break ;
		i++;
	}
	return (i);
}

char	*reverse(char *p, char *tmp, int i, int n)
{
	int		j;
	int		c;

	c = count_digits(n);
	j = 0;
	if (n < 0)
	{
		j++;
		c++;
	}
	while (j < c)
	{
		p[j] = tmp[i - 1];
		j++;
		i--;
	}
	p[j] = '\0';
	return (p);
}

char	*ft_itoa(int n)
{
	char	*p;
	char	tmp[count_digits(n)];
	size_t	i;
	size_t	c;
	size_t	cpy;

	c = count_digits(n);
	i = 0;
	if (n < 0)
		c++;
	if (!(p = (char *)malloc(c + 1)))
		return (NULL);
	cpy = n;
	if (n < 0)
	{
		i++;
		p[0] = '-';
		cpy = cpy * (-1);
	}
	while (i++ < c)
	{
		tmp[i] = (cpy % 10) + '0';
		cpy = cpy / 10;
	}
	return (reverse(p, tmp, i, n));
}
