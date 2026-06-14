/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 21:06:19 by halbit            #+#    #+#             */
/*   Updated: 2025/08/29 20:46:52 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;

	if (size == 0 || nmemb == 0)
	{
		new = malloc(1);
		if (!new)
			return (NULL);
		return (new);
	}
	new = malloc(size * nmemb);
	if (!new)
		return (NULL);
	ft_bzero(new, size * nmemb);
	return (new);
}
