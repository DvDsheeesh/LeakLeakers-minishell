/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:22 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/24 03:46:33 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_node(struct s_program_info *info, struct s_env *curr,
		struct s_env *prev)
{
	if (prev)
		prev->next = curr->next;
	else
		info->env_list = curr->next;
	if (curr->content)
		free(curr->content);
	free(curr);
}

static void	remove_env_node(struct s_program_info *info, char *key)
{
	struct s_env	*curr;
	struct s_env	*prev;
	int				len;

	if (!key || !info || !info->env_list)
		return ;
	curr = info->env_list;
	prev = NULL;
	while (curr)
	{
		len = get_env_key_len(curr->content);
		if (curr->content && (int)ft_strlen(key) == len
			&& ft_strncmp(curr->content, key, len) == 0)
		{
			delete_node(info, curr, prev);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static int	print_unset_error(char *arg)
{
	ft_putstr_fd("ShellWeDance: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	ft_unset(char **args, struct s_program_info *info)
{
	int	i;
	int	status;

	if (!args || !info)
		return (0);
	i = 1;
	status = 0;
	while (args[i])
	{
		if (is_valid_key(args[i]))
			remove_env_node(info, args[i]);
		else
			status = print_unset_error(args[i]);
		i++;
	}
	return (status);
}
