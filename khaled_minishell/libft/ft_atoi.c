/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:45:58 by kal-haj-          #+#    #+#             */
/*   Updated: 2025/08/10 19:10:52 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_space(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	out;

	i = 0;
	out = 0;
	sign = 1;
	while (ft_space(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		out = out * 10 + (nptr[i] - '0');
		i++;
	}
	return (out * sign);
}
/*
int	main(void)
{
	printf("%d\n",atoi(" -2g00"));
	printf("%d\n",ft_atoi(" -2g00"));
	printf("%d\n",atoi("\t\r    2147483647"));
	printf("%d\n",ft_atoi("\t\r    2147483647"));
	printf("%d\n",atoi("  --2fd2"));
	printf("%d\n",ft_atoi("  --2fd2"));
}
*/
