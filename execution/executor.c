/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 21:08:06 by halbit            #+#    #+#             */
/*   Updated: 2026/06/14 20:51:19 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_cmd *cmd, t_info *info, char *path)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->infile != -1)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile != -1)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	execve(path, cmd->command_args, info->env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->command_args[0], 2);
	ft_putendl_fd(": execve failed", 2);
	exit(1);
}

static int	cmd_not_found(char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

static int	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	execute(t_cmd *cmd, t_info *info)
{
	char	*path;
	pid_t	pid;

	if (!cmd || !cmd->command_args || !cmd->command_args[0])
		return (0);
	if (is_builtin(cmd->command_args[0]))
		return (exec_builtin(cmd, info));
	path = get_path(cmd->command_args[0], info->env);
	if (!path)
		return (cmd_not_found(cmd->command_args[0]));
	pid = fork();
	if (pid == -1)
	{
		free(path);
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		child_process(cmd, info, path);
	free(path);
	return (wait_child(pid));
}
