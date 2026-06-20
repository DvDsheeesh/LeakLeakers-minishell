/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:23:58 by melshata          #+#    #+#             */
/*   Updated: 2025/08/26 22:19:03 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*aa;

	aa = malloc(sizeof(t_list));
	if (!aa)
		return (NULL);
	aa->content = content;
	aa->next = NULL;
	return (aa);
}
