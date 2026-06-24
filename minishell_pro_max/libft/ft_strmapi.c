/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:16:39 by mohammad          #+#    #+#             */
/*   Updated: 2025/08/26 21:59:54 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*cc;

	if (!s || !f)
		return (NULL);
	cc = ft_strdup(s);
	if (!cc)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cc[i] = f (i, s[i]);
		i++;
	}
	return (cc);
}
