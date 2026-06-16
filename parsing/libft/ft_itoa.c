/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:40:34 by mohammad          #+#    #+#             */
/*   Updated: 2025/08/23 21:52:39 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_int_length(long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	long	num;

	num = n;
	s = (char *)malloc (my_int_length(num) + 1);
	if (!s)
		return (NULL);
	s[my_int_length(num)] = '\0';
	i = 0;
	if (num < 0)
	{
		s[0] = '-';
		num = -num;
		i = 1;
	}
	if (num == 0)
		s[0] = '0';
	while (num)
	{
		s[my_int_length(num) - 1 + i] = (char)((num % 10) + 48);
		num /= 10;
	}
	return (s);
}
