/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:46:19 by mohammad          #+#    #+#             */
/*   Updated: 2025/08/26 21:59:33 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;

	if (!s1 || !s2)
		return (NULL);
	c = (char *)malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!c)
		return (NULL);
	ft_bzero ((void *)c, ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_strlcpy (c, s1, ft_strlen(s1) + 1);
	ft_strlcat (c, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	c[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (c);
}
