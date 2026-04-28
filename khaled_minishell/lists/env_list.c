/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:01 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 20:25:02 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct s_env	*env_list_new_node(char *value)
{
	struct s_env	*node;

	node = malloc(sizeof(struct s_env));
	if (!node)
		return (NULL);
	node->content = value;
	node->next = NULL;
	return (node);
}

struct s_env	*env_list_last_node(struct s_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	env_list_add_back(struct s_env **lst, struct s_env *new)
{
	struct s_env	*lastnode;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lastnode = env_list_last_node(*lst);
	lastnode->next = new;
}

void	get_env_list(struct s_env **env_list, char **envp,
		struct s_program_info *program)
{
	int				i;
	struct s_env	*new_node;
	char			*content_copy;

	i = 0;
	while (envp[i])
	{
		content_copy = ft_strdup(envp[i]);
		alloc_handling(content_copy, program);
		new_node = env_list_new_node(content_copy);
		alloc_handling(new_node, program);
		env_list_add_back(env_list, new_node);
		i++;
	}
}

char	*get_env_var_value(char *var_name, struct s_env *env_list)
{
	size_t	var_name_length;

	var_name_length = ft_strlen(var_name);
	while (env_list)
	{
		if (ft_strlen(env_list->content) >= var_name_length)
			if (!ft_strncmp(env_list->content, var_name, var_name_length)
				&& env_list->content[var_name_length] == '=')
				return (ft_strdup(&env_list->content[var_name_length + 1]));
		env_list = env_list->next;
	}
	return (ft_strdup(""));
}
