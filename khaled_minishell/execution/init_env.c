/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:24:11 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/24 03:47:27 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_shlvl_update(struct s_program_info *info, int level)
{
	char	*new_val;

	if (level < 0)
		level = 0;
	else if (level >= 1000)
	{
		ft_putendl_fd("ShellWeDance: warning: shell level too high", 2);
		level = 1;
	}
	new_val = ft_itoa(level);
	if (!new_val)
	{
		perror("ShellWeDance: malloc");
		destroy_program_info(info);
		exit(EXIT_FAILURE);
	}
	update_env_var(info, "SHLVL", new_val);
	free(new_val);
}

static void	increment_shlvl(struct s_program_info *info)
{
	struct s_env	*node;
	int				level;

	node = find_env_node(info->env_list, "SHLVL");
	if (node && node->content)
	{
		if (ft_strlen(node->content) >= 6)
			level = ft_atoi(node->content + 6) + 1;
		else
			level = 1;
		handle_shlvl_update(info, level);
	}
	else
		update_env_var(info, "SHLVL", "1");
}

void	init_basic_env(struct s_program_info *info)
{
	char	cwd[1024];

	if (!info->env_list)
	{
		if (getcwd(cwd, sizeof(cwd)))
			update_env_var(info, "PWD", cwd);
		else
			perror("ShellWeDance: getcwd");
		update_env_var(info, "SHLVL", "1");
		update_env_var(info, "_", "/usr/bin/env");
	}
	else
		increment_shlvl(info);
}
