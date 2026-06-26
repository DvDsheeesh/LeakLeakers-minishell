/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 23:50:27 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 10:31:34 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*env_new(char *element)
{
	t_env	*node;
	char	*eq;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	eq = ft_strchr(element, '=');
	if (eq)
	{
		node->var = ft_substr(element, 0, eq - element);
		node->value = ft_strdup(eq + 1);
	}
	else
	{
		node->var = ft_strdup(element);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

t_env	*extract_env(char **env)
{
	t_env	*head;
	t_env	*cur;
	t_env	*node;
	int		i;

	if (!env || !env[0])
		return (NULL);
	head = NULL;
	cur = NULL;
	i = 0;
	while (env[i])
	{
		node = env_new(env[i]);
		if (!node)
			return (head);
		if (!head)
			head = node;
		else
			cur->next = node;
		cur = node;
		i++;
	}
	return (head);
}
