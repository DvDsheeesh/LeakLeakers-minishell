/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:01:51 by mohammad          #+#    #+#             */
/*   Updated: 2025/08/26 21:59:43 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_chrfnd(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] && set[i] != c)
		i++;
	if (set[i])
		return (1);
	else
		return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	f;
	size_t	e;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && my_chrfnd(set, s1[i]))
		i++;
	f = i;
	while (s1[i])
	{
		if (!my_chrfnd(set, s1[i]))
			e = i;
		i++;
	}
	return (ft_substr(s1, f, e - f + 1));
}
