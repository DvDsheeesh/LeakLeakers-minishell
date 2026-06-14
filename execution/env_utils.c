/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 21:55:44 by halbit            #+#    #+#             */
/*   Updated: 2026/06/14 20:06:28 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_find_idx(char **env, char *key, int klen)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, klen) == 0
			&& (env[i][klen] == '=' || env[i][klen] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	*env_get(char **env, char *key)
{
	int	klen;
	int	i;

	klen = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, klen) == 0 && env[i][klen] == '=')
			return (env[i] + klen + 1);
		i++;
	}
	return (NULL);
}

static int	env_append(t_info *info, char *entry)
{
	int		size;
	char	**new_env;

	size = 0;
	while (info->env[size])
		size++;
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (1);
	ft_memcpy(new_env, info->env, sizeof(char *) * size);
	new_env[size] = ft_strdup(entry);
	new_env[size + 1] = NULL;
	if (!new_env[size])
		return (free(new_env), 1);
	free(info->env);
	info->env = new_env;
	return (0);
}

int	env_update(t_info *info, char *entry)
{
	char	*eq;
	int		klen;
	int		idx;

	eq = ft_strchr(entry, '=');
	if (eq)
		klen = (int)(eq - entry);
	else
		klen = (int)ft_strlen(entry);
	idx = env_find_idx(info->env, entry, klen);
	if (idx >= 0)
	{
		free(info->env[idx]);
		info->env[idx] = ft_strdup(entry);
		return (!info->env[idx]);
	}
	return (env_append(info, entry));
}

int	env_set(t_info *info, char *key, char *val)
{
	char	*tmp;
	char	*entry;
	int		ret;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (1);
	if (val)
		entry = ft_strjoin(tmp, val);
	else
		entry = ft_strjoin(tmp, "");
	free(tmp);
	if (!entry)
		return (1);
	ret = env_update(info, entry);
	free(entry);
	return (ret);
}
