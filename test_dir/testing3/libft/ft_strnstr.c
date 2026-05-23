/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:04:57 by melshata          #+#    #+#             */
/*   Updated: 2025/08/26 22:40:05 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char *big, char *little, size_t i)
{
	size_t	j;

	j = 0;
	while (big[i] && little[j])
	{
		if (big[i] != little[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		t;

	i = 0;
	t = 0;
	if (!(char)little[0])
		return ((char *)big);
	if (len == 0 || !(char)big[0])
		return (NULL);
	if ((unsigned int)ft_strlen((char *)little) > (unsigned int)len)
		return (NULL);
	while (big[i] && i < len - ft_strlen((char *)little) + 1)
	{
		if (big[i] == little[0] && t == 0)
		{
			if (check((char *)big, (char *)little, i))
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
