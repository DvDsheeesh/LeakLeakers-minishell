/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:46:09 by kal-haj-          #+#    #+#             */
/*   Updated: 2025/08/07 15:20:19 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}
/*
int	main(void)
{
	char	src[] = "khaled";
	char	dst[8];
		char src1[] = "khaled";
		char dst1[8];

	printf("%zu\n", ft_strlcpy(dst,src, 9));
	printf("%s\n", dst);
		printf("%zu\n", strlcpy(dst1,src1, 9));
	printf("%s", dst);
	return (0);
}
*/
