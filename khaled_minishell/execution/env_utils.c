/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:27 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/20 08:54:34 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_key_len(char *content)
{
	int	i;

	i = 0;
	if (!content)
		return (0);
	while (content[i] && content[i] != '=')
		i++;
	return (i);
}

struct s_env	*find_env_node(struct s_env *env, char *key)
{
	int	len;

	if (!key)
		return (NULL);
	while (env)
	{
		if (!env->content)
		{
			env = env->next;
			continue ;
		}
		len = get_env_key_len(env->content);
		if ((int)ft_strlen(key) == len && ft_strncmp(env->content, key,
				len) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static char	*create_env_string(char *key, char *value)
{
	char	*tmp;
	char	*new_content;

	if (!key)
		return (NULL);
	if (!value)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	new_content = ft_strjoin(tmp, value);
	free(tmp);
	return (new_content);
}

void	update_env_var(struct s_program_info *info, char *key, char *value)
{
	struct s_env	*node;
	char			*new_content;

	if (!info || !key)
		return ;
	new_content = create_env_string(key, value);
	if (!new_content)
		return ;
	node = find_env_node(info->env_list, key);
	if (node)
	{
		if (node->content)
			free(node->content);
		node->content = new_content;
	}
	else
	{
		node = env_list_new_node(new_content);
		if (node)
			env_list_add_back(&info->env_list, node);
		else
			free(new_content);
	}
}
