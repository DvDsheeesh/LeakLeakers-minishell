/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_putnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:46:39 by melshata          #+#    #+#             */
/*   Updated: 2025/09/11 11:32:14 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftpf_putnbr(int n, int i)
{
	if (n == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write (1, "-", 1);
		i++;
		n *= -1;
	}
	if (n > 9)
		i = ftpf_putnbr(n / 10, i);
	n = n % 10 + '0';
	write (1, &n, 1);
	return (i + 1);
}

int	ftpf_putuns(unsigned int u, int i)
{
	if (u > 9)
		i = ftpf_putuns(u / 10, i);
	u = u % 10 + '0';
	write (1, &u, 1);
	return (i + 1);
}
