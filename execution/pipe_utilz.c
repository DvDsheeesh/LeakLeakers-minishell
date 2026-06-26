/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utilz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 18:04:44 by halbit            #+#    #+#             */
/*   Updated: 2026/06/26 21:37:41 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_other_fds(t_cmd *head, t_cmd *cur)
{
	t_cmd	*cmd;

	cmd = head;
	while (cmd)
	{
		if (cmd != cur)
		{
			if (cmd->infile != -1)
			{
				close(cmd->infile);
				cmd->infile = -1;
			}
			if (cmd->outfile != -1)
			{
				close(cmd->outfile);
				cmd->outfile = -1;
			}
		}
		cmd = cmd->next;
	}
}

int	count_cmds(t_cmd *cmd)
{
	int	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

void	no_path(t_cmd *cmd, t_info *info)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->command_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	free(info->pipe_pids);
	free_cmds(info->cmds_head);
	free_vars(info);
	exit(127);
}
