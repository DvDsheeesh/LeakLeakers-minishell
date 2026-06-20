/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:40:01 by halbit            #+#    #+#             */
/*   Updated: 2026/06/20 13:41:13 by melshata         ###   ########.fr       */
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

int	exec_builtin(t_cmd *cmd, t_info *info)
{
	char	*n;

	n = cmd->command_args[0];
	if (ft_strncmp(n, "echo", 5) == 0)
		return (ft_echo(cmd->command_args));
	if (ft_strncmp(n, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(n, "env", 4) == 0)
		return (ft_env(info->env));
	if (ft_strncmp(n, "exit", 5) == 0)
		return (ft_exit(cmd->command_args, info));
	if (ft_strncmp(n, "export", 7) == 0)
		return (ft_export(cmd->command_args, info));
	if (ft_strncmp(n, "unset", 6) == 0)
		return (ft_unset(cmd->command_args, info));
	return (ft_cd(cmd->command_args, info));
}
