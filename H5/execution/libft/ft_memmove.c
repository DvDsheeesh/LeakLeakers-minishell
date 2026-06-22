/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:02:19 by halbit            #+#    #+#             */
/*   Updated: 2025/08/29 21:57:26 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (d < s)
	{
		while (n > 0)
		{
			d[i] = s[i];
			i++;
			n--;
		}
	}
	else if (d > s)
	{
		while (0 < n--)
			d[n] = s[n];
	}
	else
		return (dest);
	return (dest);
}
