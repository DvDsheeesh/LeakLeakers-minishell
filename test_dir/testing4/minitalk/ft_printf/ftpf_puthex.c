/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_puthex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 08:48:56 by melshata          #+#    #+#             */
/*   Updated: 2025/09/15 11:02:33 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	phex_part(size_t n, int i, char const *hs)
{
	if (n > 15)
		i = phex_part(n / 16, i, hs);
	n = hs[n % 16];
	write (1, &n, 1);
	return (i + 1);
}

int	ftpf_puthex(int n, int i, char c)
{
	unsigned int	num;

	num = n;
	if (c == 'x')
		i = phex_part(num, i, "0123456789abcdef");
	if (c == 'X')
		i = phex_part(num, i, "0123456789ABCDEF");
	return (i);
}

int	ftpf_putptr(void *p, int i)
{
	size_t	n;

	n = (size_t)p;
	if (n == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	if (n == 0)
		return (0);
	write(1, "0x", 2);
	i = phex_part(n, i, "0123456789abcdef");
	return (i + 2);
}
