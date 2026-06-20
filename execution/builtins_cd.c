/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 20:50:01 by halbit            #+#    #+#             */
/*   Updated: 2026/06/20 13:41:08 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

static char	*cd_get_target(char **args, char **env)
{
	char	*target;

	if (!args[1] || ft_strncmp(args[1], "--", 3) == 0)
	{
		target = env_get(env, "HOME");
		if (!target)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
		return (target);
	}
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		target = env_get(env, "OLDPWD");
		if (!target)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), NULL);
		ft_putendl_fd(target, 1);
		return (target);
	}
	return (args[1]);
}

static void	cd_update_env(t_info *info, char *old)
{
	char	*cwd;

	if (old)
		env_set(info, "OLDPWD", old);
	free(old);
	cwd = getcwd(NULL, 0);
	if (cwd)
		env_set(info, "PWD", cwd);
	free(cwd);
}

int	ft_cd(char **args, t_info *info)
{
	char	*target;
	char	*old;

	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	target = cd_get_target(args, info->env);
	if (!target)
		return (1);
	old = getcwd(NULL, 0);
	if (chdir(target) == -1)
		return (free(old), cd_error(target));
	cd_update_env(info, old);
	return (0);
}
