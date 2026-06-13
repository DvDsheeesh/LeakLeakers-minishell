/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:20:00 by melshata          #+#    #+#             */
/*   Updated: 2025/08/26 22:22:14 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen((char *)s);
	while (s[i])
	{
		if (s[i] == (char)c)
			j = i;
		i++;
	}
	if (s[j] == (char)c)
		return ((char *)s + j);
	else
		return (NULL);
}
