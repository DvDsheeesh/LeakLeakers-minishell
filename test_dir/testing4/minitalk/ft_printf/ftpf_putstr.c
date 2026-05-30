/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_putstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:20:17 by melshata          #+#    #+#             */
/*   Updated: 2025/09/11 11:25:50 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftpf_putchr(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ftpf_putstr(char *s)
{
	int	i;

	if (!s)
	{
		write (1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}
