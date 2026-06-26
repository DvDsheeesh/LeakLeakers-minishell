/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 18:04:44 by halbit            #+#    #+#             */
/*   Updated: 2026/06/26 17:43:30 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_child_io(t_cmd *cmd, int prev, int pw)
{
	if (cmd->infile != -1)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	else if (prev != -1)
		dup2(prev, STDIN_FILENO);
	if (cmd->outfile != -1)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	else if (pw != -1)
		dup2(pw, STDOUT_FILENO);
	if (prev != -1)
		close(prev);
	if (pw != -1)
		close(pw);
}

void	no_path_exit(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->command_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

static void	pipe_child(t_cmd *cmd, t_info *info, int prev, int *pw)
{
	char	*path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close (pw[0]);
	pipe_child_io(cmd, prev, pw[1]);
	if (!cmd->command_args || !cmd->command_args[0])
		exit(0);
	if (is_builtin(cmd->command_args[0]))
		exit(exec_builtin(cmd, info, 1));
	path = get_path(cmd->command_args[0], info->env);
	if (!path)
		no_path_exit(cmd);
	envp = env_to_arr(info->env);
	execve(path, cmd->command_args, envp);
	free_arr(envp);
	free(path);
	exit(1);
}

static int	pipe_run_one(t_cmd *cmd, t_info *info, int *prev, pid_t *pid)
{
	int	pipefd[2];

	*pid = -1;
	pipefd[0] = -1;
	pipefd[1] = -1;
	if (cmd->next && pipe(pipefd) == -1)
		return (perror("minishell: pipe"), 1);
	*pid = fork();
	if (*pid == -1)
		perror("minishell: fork");
	if (*pid == 0)
		pipe_child(cmd, info, *prev, pipefd);
	if (*prev != -1)
		close(*prev);
	if (cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev = pipefd[0];
	}
	return (*pid == -1);
}

static int	pipe_wait_all(pid_t *pids, int n)
{
	int	status;
	int	ret;
	int	i;

	status = 0;
	ret = 0;
	i = 0;
	while (i < n)
	{
		if (pids[i] != -1)
			waitpid(pids[i], &status, 0);
		if (i == n - 1 && pids[i] != -1)
		{
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ret = exit_child(status);
		}
		i++;
	}
	free(pids);
	return (ret);
}

int	execute_pipeline(t_cmd *cmds, t_info *info)
{
	t_cmd	*cmd;
	pid_t	*pids;
	int		n;
	int		i;
	int		prev;

	n = 0;
	cmd = cmds;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	pids = malloc(sizeof(pid_t) * n);
	if (!pids)
		return (perror("minishell"), 1);
	i = 0;
	prev = -1;
	cmd = cmds;
	while (cmd)
	{
		pipe_run_one(cmd, info, &prev, &pids[i++]);
		cmd = cmd->next;
	}
	return (pipe_wait_all(pids, n));
}
