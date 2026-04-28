/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:16 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 21:36:48 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(struct s_commands *cmd, struct s_program_info *info)
{
	char	*command;

	if (!cmd || !cmd->command_args || !cmd->command_args[0])
		return (0);
	command = cmd->command_args[0];
	if (!ft_strcmp(command, "echo"))
		return (ft_echo(cmd->command_args));
	if (!ft_strcmp(command, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(command, "env"))
		return (ft_env(info->env_list));
	if (!ft_strcmp(command, "exit"))
		return (ft_exit(cmd->command_args, info));
	if (!ft_strcmp(command, "export"))
		return (ft_export(cmd->command_args, info));
	if (!ft_strcmp(command, "unset"))
		return (ft_unset(cmd->command_args, info));
	if (!ft_strcmp(command, "cd"))
		return (ft_cd(cmd->command_args, info));
	return (0);
}
