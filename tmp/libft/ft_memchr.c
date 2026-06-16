/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:34:11 by melshata          #+#    #+#             */
/*   Updated: 2025/08/19 16:59:01 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ss;

	ss = (char *)s;
	if (n == 0)
		return (NULL);
	i = 0;
	while (ss[i] != (char)c && i < n - 1)
		i++;
	if (ss[i] == (char)c)
		return ((void *)(ss + i));
	else
		return (NULL);
}
