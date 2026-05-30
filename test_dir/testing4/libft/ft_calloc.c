/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:19:55 by melshata          #+#    #+#             */
/*   Updated: 2025/08/31 18:41:41 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		p = malloc(1);
		if (!p)
			return (NULL);
	}
	else
	{
		p = malloc(nmemb * size);
		if (!p)
			return (NULL);
		ft_bzero(p, nmemb * size);
	}
	return (p);
}
