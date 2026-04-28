/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:14 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/24 03:45:55 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_target_path(char **args, struct s_program_info *info)
{
	struct s_env	*home_node;

	if (args && args[1])
		return (args[1]);
	home_node = find_env_node(info->env_list, "HOME");
	if (!home_node || !home_node->content || ft_strlen(home_node->content) <= 5)
	{
		ft_putendl_fd("ShellWeDance: cd: HOME not set", 2);
		return (NULL);
	}
	return (home_node->content + 5);
}

static void	update_work_dirs(struct s_program_info *info, char *old_pwd)
{
	char	cwd[1024];

	if (old_pwd)
		update_env_var(info, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(info, "PWD", cwd);
	else
		perror("ShellWeDance: cd: getcwd");
}

int	ft_cd(char **args, struct s_program_info *info)
{
	char	*path;
	char	*old_pwd;
	char	cwd[1024];

	if (!args || !info)
		return (1);
	path = get_target_path(args, info);
	if (!path)
		return (1);
	old_pwd = NULL;
	if (getcwd(cwd, sizeof(cwd)))
		old_pwd = ft_strdup(cwd);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("ShellWeDance: cd: ", 2);
		perror(path);
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	update_work_dirs(info, old_pwd);
	if (old_pwd)
		free(old_pwd);
	return (0);
}
