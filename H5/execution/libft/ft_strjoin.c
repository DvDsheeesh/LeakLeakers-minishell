/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 23:00:08 by halbit            #+#    #+#             */
/*   Updated: 2025/08/26 16:33:27 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jo;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	jo = malloc(sizeof(char) * (len + 1));
	if (!jo)
		return (0);
	ft_strlcpy(jo, s1, len + 1);
	ft_strlcat(jo, s2, len + 1);
	return (jo);
}
