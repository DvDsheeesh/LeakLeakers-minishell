/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:33:25 by kal-haj-          #+#    #+#             */
/*   Updated: 2025/08/09 16:50:25 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = (char *)s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return (&ptr[i]);
		i--;
	}
	return (0);
}
/*
int	main(void)
{
		char s[] = "khalfjoissedsdhuisdkhalfjoissedsdhuisd";
		char s1[] = "khalfjoissedsdhuisdkhalfjoissedsdhuisd";

		printf("%s\n", ft_strrchr(s, 'k'));
		printf("%s", strrchr(s1, 'k'));
		return (0);
}
*/
