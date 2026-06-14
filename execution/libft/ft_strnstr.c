/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:24:52 by halbit            #+#    #+#             */
/*   Updated: 2025/08/26 16:39:00 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*b;
	char			*l;

	i = 0;
	j = 0;
	b = (char *)big;
	l = (char *)little;
	if (l[j] == 0)
		return (&b[i]);
	while (b[i] > 0 && i < len)
	{
		while (b[i + j] == l[j] && (i + j) < len)
		{
			if (l[j + 1] == 0)
				return (&b[i]);
			j ++;
		}
		j = 0;
		i ++;
	}
	return (0);
}
