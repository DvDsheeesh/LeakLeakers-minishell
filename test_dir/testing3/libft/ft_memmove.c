/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:12:30 by melshata          #+#    #+#             */
/*   Updated: 2025/08/26 18:58:22 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	int		rev;
	char	*dd;
	char	*ss;

	if (dest < src)
		rev = 0;
	else
		rev = 1;
	dd = (char *)dest;
	ss = (char *)src;
	i = (n * rev) - rev;
	while (i != n - (n + 1) * rev)
	{
		*(dd + i) = *(ss + i);
		i += 1 - (2 * rev);
	}
	return (dest);
}
