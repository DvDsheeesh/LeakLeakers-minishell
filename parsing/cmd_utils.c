/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 23:46:10 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 02:28:49 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*last_command(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_cmd	*create_command_node(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->command_args = NULL;
	node->redirs = NULL;
	node->infile = -1;
	node->outfile = -1;
	node->next = NULL;
	return (node);
}

t_redir	*new_redir(t_redir_type type, char *file)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->file = ft_strdup(file);
	r->next = NULL;
	return (r);
}
