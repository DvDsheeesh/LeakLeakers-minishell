/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:34 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 21:42:11 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	setup_single_builtin(struct s_commands *cmd,
		struct s_program_info *info)
{
	info->orig_in = dup(STDIN_FILENO);
	info->orig_out = dup(STDOUT_FILENO);
	if (info->orig_in == -1 || info->orig_out == -1)
	{
		if (info->orig_in != -1)
			close(info->orig_in);
		if (info->orig_out != -1)
			close(info->orig_out);
		info->exit_status = 1;
		return (0);
	}
	if (handle_redirections(cmd) != -1)
		info->exit_status = exec_builtin(cmd, info);
	else
		info->exit_status = 1;
	return (1);
}

static int	exec_single_builtin(struct s_commands *cmd,
		struct s_program_info *info)
{
	if (!cmd->next && cmd->command_args && cmd->command_args[0]
		&& is_builtin(cmd->command_args[0]))
	{
		if (setup_single_builtin(cmd, info))
		{
			dup2(info->orig_in, STDIN_FILENO);
			dup2(info->orig_out, STDOUT_FILENO);
			close(info->orig_in);
			close(info->orig_out);
		}
		info->orig_in = -1;
		info->orig_out = -1;
		return (1);
	}
	return (0);
}

static void	exec_parent_process(struct s_commands *cmd, int *prev_fd,
		int pipe_fd[2])
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	if (cmd->heredoc_fd != -1)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
}

void	executor(struct s_program_info *info)
{
	struct s_commands	*cmd;
	int					pipe_fd[2];
	int					prev_fd;
	pid_t				pid;

	cmd = info->command_list;
	prev_fd = -1;
	if (exec_single_builtin(cmd, info))
		return ;
	setup_execution_signals();
	while (cmd)
	{
		if (create_pipe_and_fork(cmd, pipe_fd, &pid) == -1)
			break ;
		if (pid == 0)
			exec_child_process(cmd, info, prev_fd, pipe_fd);
		else
			exec_parent_process(cmd, &prev_fd, pipe_fd);
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_for_executor(pid, info);
}
