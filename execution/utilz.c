/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:52:22 by halbit            #+#    #+#             */
/*   Updated: 2026/06/26 18:09:10 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	current_env_proc(t_env **cur, char ***arr, char **tmp, int *i)
{
	*tmp = ft_strjoin((*cur)->var, "=");
	if ((*cur)->value)
		(*arr)[*i] = ft_strjoin(*tmp, (*cur)->value);
	else
		(*arr)[*i] = ft_strjoin(*tmp, "");
	free(*tmp);
	(*cur) = (*cur)->next;
	(*i)++;
}

char	**env_to_arr(t_env *env)
{
	t_env	*cur;
	char	**arr;
	char	*tmp;
	int		n;
	int		i;

	n = 0;
	cur = env;
	while (cur)
	{
		n++;
		cur = cur->next;
	}
	arr = malloc(sizeof(char *) * (n + 1));
	if (!arr)
		return (NULL);
	cur = env;
	i = 0;
	while (cur)
		current_env_proc(&cur, &arr, &tmp, &i);
	arr[i] = NULL;
	return (arr);
}

static int	open_redir_in(t_cmd *cmd, t_redir *r, t_info *info)
{
	int	fd;

	if (r->type == REDIR_HEREDOC)
	{
		setup_execution_signals();
		fd = handle_heredoc(r->file, info, cmd);
		setup_inline_signals();
		if (fd == -1)
			return (1);
	}
	else
	{
		fd = open(r->file, O_RDONLY);
		if (fd == -1)
		{
			info->exit_status = 1;
			return (perror(r->file), 1);
		}
	}
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = fd;
	return (0);
}

static int	open_redir_out(t_cmd *cmd, t_redir *r)
{
	int	fd;
	int	flags;

	if (r->type == REDIR_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(r->file, flags, 0644);
	if (fd == -1)
		return (perror(r->file), 1);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = fd;
	return (0);
}

int	open_redirections(t_cmd *cmds, t_info *info)
{
	t_cmd	*cmd;
	t_redir	*r;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == REDIR_IN || r->type == REDIR_HEREDOC)
			{
				if (open_redir_in(cmd, r, info))
					return (1);
			}
			else if (open_redir_out(cmd, r))
				return (1);
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
