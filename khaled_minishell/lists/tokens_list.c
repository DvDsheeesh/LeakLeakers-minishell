/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:06 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 20:25:07 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct s_tokens	*tokens_list_new_node(char *value)
{
	struct s_tokens	*node;

	node = malloc(sizeof(struct s_tokens));
	if (!node)
		return (NULL);
	node->content = value;
	node->next = NULL;
	node->previous = NULL;
	node->type = -1;
	return (node);
}

struct s_tokens	*tokens_list_last_node(struct s_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	tokens_list_add_back(struct s_tokens **lst, struct s_tokens *new)
{
	struct s_tokens	*lastnode;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lastnode = tokens_list_last_node(*lst);
	lastnode->next = new;
	new->previous = lastnode;
}
