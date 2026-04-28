/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:30 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/19 02:41:41 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_external_cmd(struct s_commands *cmd,
		struct s_program_info *info)
{
	char	**env_array;
	char	*path;

	env_array = env_to_char_array(info->env_list);
	if (!env_array)
	{
		destroy_program_info(info);
		exit(1);
	}
	path = get_cmd_path(cmd->command_args[0], env_array);
	if (!path)
	{
		handle_cmd_error(cmd->command_args[0], env_array, info);
	}
	execve(path, cmd->command_args, env_array);
	handle_cmd_error(cmd->command_args[0], env_array, info);
}

void	exec_child_process(struct s_commands *cmd, struct s_program_info *info,
		int prev_fd, int pipe_fd[2])
{
	int	ret;

	restore_default_signals();
	handle_child_pipes(cmd, prev_fd, pipe_fd);
	if (handle_redirections(cmd) == -1)
	{
		destroy_program_info(info);
		exit(1);
	}
	if (!cmd->command_args || !cmd->command_args[0])
	{
		destroy_program_info(info);
		exit(0);
	}
	if (is_builtin(cmd->command_args[0]))
	{
		ret = exec_builtin(cmd, info);
		destroy_program_info(info);
		exit(ret);
	}
	execute_external_cmd(cmd, info);
}
