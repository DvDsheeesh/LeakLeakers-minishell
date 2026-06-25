/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 21:08:06 by halbit            #+#    #+#             */
/*   Updated: 2026/06/25 22:32:14 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_builtin_redir(t_cmd *cmd, t_info *info)
{
	int	saved[2];
	int	ret;

	if (cmd->infile == -1 && cmd->outfile == -1)
		return (exec_builtin(cmd, info));
	saved[0] = dup(STDIN_FILENO);
	saved[1] = dup(STDOUT_FILENO);
	if (cmd->infile != -1)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile != -1)
		dup2(cmd->outfile, STDOUT_FILENO);
	ret = exec_builtin(cmd, info);
	dup2(saved[0], STDIN_FILENO);
	dup2(saved[1], STDOUT_FILENO);
	close(saved[0]);
	close(saved[1]);
	return (ret);
}

static void	child_process(t_cmd *cmd, t_info *info, char *path)
{
	char	**envp;

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
	envp = env_to_arr(info->env);
	default_signals();
	info->exit_status = execve(path, cmd->command_args, envp);
	free_arr(envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->command_args[0], 2);
	ft_putendl_fd(": execve failed", 2);
	exit(1);
}

static int	cmd_not_found(char *name, t_info *info)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": command not found", 2);
	info->exit_status = 127;
	return (127);
}

static int	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (0);
}

int	execute(t_cmd *cmd, t_info *info)
{
	char	*path;
	pid_t	pid;

	if (!cmd || !cmd->command_args || !cmd->command_args[0])
		return (0);
	if (cmd->next)
		return (execute_pipeline(cmd, info));
	if (is_builtin(cmd->command_args[0]))
		return (exec_builtin_redir(cmd, info));
	path = get_path(cmd->command_args[0], info->env);
	if (!path)
		return (cmd_not_found(cmd->command_args[0], info));
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
