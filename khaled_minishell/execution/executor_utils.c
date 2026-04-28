/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:24:01 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/24 03:46:55 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_child_pipes(struct s_commands *cmd, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			perror("ShellWeDance: dup2");
		close(prev_fd);
	}
	if (cmd->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("ShellWeDance: dup2");
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

static void	handle_path_error(char *cmd, struct s_program_info *info)
{
	struct stat	st;
	char		*tmp;

	if (stat(cmd, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			ft_putendl_fd(": is a directory", 2);
		else
			ft_putendl_fd(": Permission denied", 2);
		destroy_program_info(info);
		exit(126);
	}
	tmp = ft_strtrim(cmd, "/");
	if (ft_strchr(cmd, '/') && tmp
		&& stat(tmp, &st) == 0 && !S_ISDIR(st.st_mode))
	{
		free(tmp);
		ft_putendl_fd(": Not a directory", 2);
		destroy_program_info(info);
		exit(126);
	}
	free(tmp);
	ft_putendl_fd(": No such file or directory", 2);
	destroy_program_info(info);
	exit(127);
}

void	handle_cmd_error(char *cmd, char **env_array,
		struct s_program_info *info)
{
	ft_putstr_fd("ShellWeDance: ", 2);
	ft_putstr_fd(cmd, 2);
	if (env_array)
		free_two_dimensional(env_array);
	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putendl_fd(": filename argument required", 2);
		destroy_program_info(info);
		exit(2);
	}
	if (ft_strchr(cmd, '/'))
		handle_path_error(cmd, info);
	else
		ft_putendl_fd(": command not found", 2);
	destroy_program_info(info);
	exit(127);
}

int	create_pipe_and_fork(struct s_commands *cmd, int pipe_fd[2], pid_t *pid)
{
	if (cmd->next && pipe(pipe_fd) == -1)
	{
		perror("ShellWeDance: pipe");
		return (-1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("ShellWeDance: fork");
		if (cmd->next)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		return (-1);
	}
	return (0);
}

void	wait_for_executor(pid_t last_pid, struct s_program_info *info)
{
	int	status;

	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			info->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			info->exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
			else if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
		}
	}
	while (waitpid(-1, NULL, 0) != -1)
		continue ;
}
