/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:22:59 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/20 19:19:55 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_path_in_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*try_build_path(char *path, char *cmd)
{
	char		*path_part;
	char		*full_path;
	struct stat	st;

	path_part = ft_strjoin(path, "/");
	if (!path_part)
		return (NULL);
	full_path = ft_strjoin(path_part, cmd);
	free(path_part);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK | X_OK) == 0 && stat(full_path, &st) == 0
		&& !S_ISDIR(st.st_mode))
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*handle_absolute_path(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*final_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		final_path = try_build_path(paths[i], cmd);
		if (final_path)
		{
			free_two_dimensional(paths);
			return (final_path);
		}
		i++;
	}
	free_two_dimensional(paths);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(cmd));
	path_env = find_path_in_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
