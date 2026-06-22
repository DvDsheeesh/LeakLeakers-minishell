/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:59:11 by halbit            #+#    #+#             */
/*   Updated: 2025/08/29 21:57:45 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*p;
	int				i;

	i = ft_strlen(s);
	p = (unsigned char *)s;
	while (i >= 0)
	{
		if (p[i] == (unsigned char)c)
			return ((char *)&p[i]);
		i --;
	}
	return (0);
}
