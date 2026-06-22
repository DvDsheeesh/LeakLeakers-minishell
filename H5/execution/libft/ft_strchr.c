/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:17:43 by halbit            #+#    #+#             */
/*   Updated: 2025/08/21 16:23:09 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (*p)
	{
		if (*p == (unsigned char)c)
			return ((char *)p);
		p++;
	}
	if (*p == (unsigned char)c)
		return ((char *)p);
	return (0);
}
