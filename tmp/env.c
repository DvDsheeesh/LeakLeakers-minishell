/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:51:00 by melshata          #+#    #+#             */
/*   Updated: 2026/06/13 12:09:50 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Builds a t_list from the envp array passed to main().
** Each node's content is a heap copy of the "KEY=VALUE" string.
*/
t_list	*extract_env(char **env)
{
	t_list	*head;
	int		i;

	head = NULL;
	i = 0;
	while (env && env[i])
	{
		ft_lstadd_back(&head, ft_lstnew(ms_cpy(env[i])));
		i++;
	}
	return (head);
}

/*
** Returns the value part of a "KEY=VALUE" env node,
** or NULL if the key is not found.
** The returned pointer points inside the node's content — do not free it.
*/
char	*get_env_val(t_list *env, char *key)
{
	t_list	*node;
	char	*entry;
	int		key_len;

	key_len = ms_strlen(key);
	node = env;
	while (node)
	{
		entry = (char *)node->content;
		if (ft_strncmp(entry, key, key_len) == 0 && entry[key_len] == '=')
			return (entry + key_len + 1);
		node = node->next;
	}
	return (NULL);
}
