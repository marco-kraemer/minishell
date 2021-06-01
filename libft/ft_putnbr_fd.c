/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 03:41:08 by maraurel          #+#    #+#             */
/*   Updated: 2021/02/12 03:45:32 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char digit;
	char negative;

	negative = 45;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		n = n * (-1);
		return ;
	}
	if (n < 0)
	{
		write(fd, &negative, 1);
		n = n * (-1);
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	digit = (n % 10) + '0';
	write(fd, &digit, 1);
}
