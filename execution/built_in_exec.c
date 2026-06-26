/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:40:11 by halbit            #+#    #+#             */
/*   Updated: 2026/06/26 17:41:11 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0 || ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0 || ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0 || ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (ft_strncmp(cmd, "cd", 3) == 0);
}

int	exec_builtin(t_cmd *cmd, t_info *info, int is_child)
{
	char	*n;
	int	ret;

	n = cmd->command_args[0];
	if (ft_strncmp(n, "echo", 5) == 0)
		ret = ft_echo(cmd->command_args);
	else if (ft_strncmp(n, "pwd", 4) == 0)
		ret = ft_pwd();
	else if (ft_strncmp(n, "env", 4) == 0)
		ret = ft_env(info->env);
	else if (ft_strncmp(n, "exit", 5) == 0)
		ret = ft_exit(cmd, info);
	else if (ft_strncmp(n, "export", 7) == 0)
		ret = ft_export(cmd->command_args, info);
	else if (ft_strncmp(n, "unset", 6) == 0)
		ret = ft_unset(cmd->command_args, info);
	else
		ret = ft_cd(cmd->command_args, info);
	if (is_child)
	{
		free_vars(info);
		free_cmds(cmd);
	}
	return (ret);
}
