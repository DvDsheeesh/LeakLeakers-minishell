/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:24:09 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/24 03:47:16 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	apply_heredoc(struct s_commands *cmd)
{
	if (cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("ShellWeDance: dup2");
			close(cmd->heredoc_fd);
			return (-1);
		}
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	return (0);
}

static int	apply_infile(char *file)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("ShellWeDance: ", 2);
		perror(file);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("ShellWeDance: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	apply_outfile(char *file, int mode)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_WRONLY | O_CREAT | mode, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("ShellWeDance: ", 2);
		perror(file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("ShellWeDance: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_redirections(struct s_commands *cmd)
{
	struct s_redirections_files	*file;
	int							status;

	if (apply_heredoc(cmd) == -1)
		return (-1);
	file = cmd->files_list;
	while (file)
	{
		status = 0;
		if (file->type == INFILE)
			status = apply_infile(file->name);
		else if (file->type == OUTFILE_TRUNCATE)
			status = apply_outfile(file->name, O_TRUNC);
		else if (file->type == OUTFILE_APPEND)
			status = apply_outfile(file->name, O_APPEND);
		if (status == -1)
			return (-1);
		file = file->next;
	}
	return (0);
}
