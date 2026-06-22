/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:18:10 by halbit            #+#    #+#             */
/*   Updated: 2025/08/21 16:13:37 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*r;

	r = (unsigned char *)s;
	while (n > 0)
	{
		if (*r == (unsigned char)c)
			return (r);
		else
			r++;
		n--;
	}
	return (0);
}
