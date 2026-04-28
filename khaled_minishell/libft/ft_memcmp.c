/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:54:39 by kal-haj-          #+#    #+#             */
/*   Updated: 2025/08/09 20:21:22 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int					i;
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	ptr1 = s1;
	ptr2 = s2;
	i = 0;
	while (n && ptr1[i] == ptr2[i])
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return (ptr1[i] - ptr2[i]);
}
/*
int	main(void)
{
	//char s1[] = "khaled";
	//char s2[] = "khfled";
	printf("%d\n", ft_memcmp("abcdefghij", "abcdefgxyz", 7));
	printf("%d", memcmp("abcdefghij", "abcdefgxyz", 7));
}
*/
