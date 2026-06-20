/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 21:00:17 by halbit            #+#    #+#             */
/*   Updated: 2026/06/21 00:15:13 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path_in_env(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*make_full_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = make_full_path(paths[i], cmd);
		if (!full_path)
			return (free_arr(paths), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_arr(paths), full_path);
		free(full_path);
		i++;
	}
	free_arr(paths);
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

char	*get_path(char *cmd, char **envp)
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
