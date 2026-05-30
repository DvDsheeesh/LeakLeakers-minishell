/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:40:15 by melshata          #+#    #+#             */
/*   Updated: 2025/09/15 11:22:56 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	redirect_f(char ch, va_list args)
{
	int	nn;

	nn = 0;
	if (ch == 'i' || ch == 'd')
		nn = ftpf_putnbr(va_arg(args, int), 0);
	else if (ch == 'x' || ch == 'X')
		nn = ftpf_puthex(va_arg(args, int), 0, ch);
	else if (ch == 'u')
		nn = ftpf_putuns(va_arg(args, unsigned int), 0);
	else if (ch == 'c')
		nn = ftpf_putchr(va_arg(args, int));
	else if (ch == 's')
		nn = ftpf_putstr(va_arg(args, char *));
	else if (ch == 'p')
		nn = ftpf_putptr(va_arg(args, void *), 0);
	else if (ch == '%')
		nn = ftpf_putchr('%');
	return (nn);
}

int	ft_printf(const char *sss, ...)
{
	va_list	args;
	size_t	i;
	int		num;

	i = 0;
	num = 0;
	if (sss == NULL)
		return (-1);
	va_start (args, sss);
	while (sss[i])
	{
		while (sss[i] != '%' && sss[i])
		{
			write (1, &sss[i++], 1);
			num++;
		}
		if (sss[i] == '%')
		{
			i++;
			num += redirect_f (sss[i++], args);
		}
	}
	va_end(args);
	return (num);
}
