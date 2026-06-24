/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:20:06 by melshata          #+#    #+#             */
/*   Updated: 2025/08/26 22:24:52 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dd;
	char	*ss;

	i = 0;
	dd = (char *)dest;
	ss = (char *)src;
	if (n == 0)
		return (dest);
	while (i < n)
	{
		*(dd + i) = *(ss + i);
		i++;
	}
	return (dest);
}
