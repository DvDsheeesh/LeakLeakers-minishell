/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:12:06 by kal-haj-          #+#    #+#             */
/*   Updated: 2025/08/10 18:34:20 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	ptr = (char *)big;
	i = 0;
	if (*little == '\0')
		return (ptr);
	while (i < len && ptr[i])
	{
		j = 0;
		while (ptr[i + j] == little[j] && little[j] != '\0' && i + j < len)
			j++;
		if (little[j] == '\0')
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
//	char s[] = "khaledyugukuilhl";
//	char s1[] = "guk";
	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "consectetur", 30));
		printf("%s", strnstr("lorem ipsum dolor sit amet", "consectetur", 30));
	return (0);
}
*/
