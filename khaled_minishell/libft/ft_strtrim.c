/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:07:38 by kal-haj-          #+#    #+#             */
/*   Updated: 2025/08/12 17:17:46 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	found(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		last;
	int		len;
	char	*result;

	first = 0;
	if (!s1 || !set)
		return (NULL);
	last = ft_strlen(s1);
	while (s1[first] && found(s1[first], set))
		first++;
	while (last > first && found(s1[last - 1], set))
		last--;
	len = last - first;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1 + first, len);
	result[len] = '\0';
	return (result);
}
/*
int	main(void)
{
	char	*s;

	s = ft_strtrim(NULL, NULL);
	printf("%s", s);
}
*/
