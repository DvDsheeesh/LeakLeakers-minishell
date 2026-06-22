/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 21:55:44 by halbit            #+#    #+#             */
/*   Updated: 2026/06/22 21:55:11 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_get(t_env *env, char *key)
{
	int	klen;

	klen = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->var, key, klen) == 0 && env->var[klen] == '\0')
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static t_env	*env_new_node(char *key, char *val)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->var = ft_strdup(key);
	node->value = val ? ft_strdup(val) : NULL;
	node->next = NULL;
	if (!node->var)
	{
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}

int	env_set(t_info *info, char *key, char *val)
{
	t_env	*cur;
	t_env	*node;

	cur = info->env;
	while (cur)
	{
		if (ft_strncmp(cur->var, key, ft_strlen(key) + 1) == 0)
		{
			free(cur->value);
			cur->value = val ? ft_strdup(val) : NULL;
			return (0);
		}
		cur = cur->next;
	}
	node = env_new_node(key, val);
	if (!node)
		return (1);
	if (!info->env)
	{
		info->env = node;
		return (0);
	}
	cur = info->env;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
	return (0);
}

int	env_update(t_info *info, char *entry)
{
	char	*eq;
	char	*key;
	char	*val;
	int		ret;

	eq = ft_strchr(entry, '=');
	if (eq)
	{
		key = ft_substr(entry, 0, eq - entry);
		val = ft_strdup(eq + 1);
	}
	else
	{
		key = ft_strdup(entry);
		val = NULL;
	}
	if (!key)
		return (1);
	ret = env_set(info, key, val);
	free(key);
	free(val);
	return (ret);
}