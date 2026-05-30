/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:04:52 by melshata          #+#    #+#             */
/*   Updated: 2025/08/26 21:34:40 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l2;
	t_list	*p2;
	t_list	*p;

	if (!lst || !f || !del)
		return (NULL);
	l2 = ft_lstnew(f(lst->content));
	if (!l2)
		return (NULL);
	p = lst->next;
	while (p)
	{
		p2 = ft_lstlast(l2);
		p2->next = ft_lstnew(f(p->content));
		if (!p2->next)
		{
			ft_lstclear(&l2, del);
			return (l2);
		}
		p = p->next;
	}
	return (l2);
}
