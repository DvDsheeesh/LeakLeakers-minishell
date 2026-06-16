/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:49:36 by melshata          #+#    #+#             */
/*   Updated: 2025/08/26 21:33:22 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p	;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		ft_lstdelone (*lst, del);
		*lst = p;
	}
	free (*lst);
	*lst = NULL;
}
