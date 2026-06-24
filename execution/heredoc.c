/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:40:56 by halbit            #+#    #+#             */
/*   Updated: 2026/06/25 00:31:24 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*heredoc_expand(char *line, t_env *env)
{
	t_info	tmp;
	char	*result;
	int		i;

	result = ft_strdup(line);
	if (!result)
		return (NULL);
	tmp.env = env;
	tmp.exit_status = g_signal;
	i = 0;
	while (result && result[i])
	{
		if (result[i] == '$' && result[i + 1] != '$'
			&& (ft_isalnum((unsigned char)result[i + 1])
				|| result[i + 1] == '_' || result[i + 1] == '?'))
			i = dollar_of_truth(&result, &tmp, i);
		else
			i++;
	}
	return (result);
}

static void	heredoc_write(int fd, char *line, t_env *env)
{
	char	*expanded;

	expanded = heredoc_expand(line, env);
	if (!expanded)
		return ;
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
}

static void	heredoc_child(char *delim, int write_fd, t_info *info, t_cmd *cmd)
{
	char	*line;
	int		dlen;

	setup_heredoc_signals();
	dlen = ft_strlen(delim);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delim, dlen + 1) == 0)
		{
			free(line);
			break ;
		}
		heredoc_write(write_fd, line, info->env);
		free(line);
	}
	close(write_fd);
	free_vars(info);
	free_cmds(cmd);
	exit(g_signal);
}

static int	heredoc_parent(int *pipefd, pid_t pid)
{
	int	status;

	status = 0;
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(pipefd[0]);
		g_signal = 130;
		return (-1);
	}
	return (pipefd[0]);
}

int	handle_heredoc(char *delim, t_info *info, t_cmd *cmd)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_child(delim, pipefd[1], info, cmd);
	}
	return (heredoc_parent(pipefd, pid));
}
