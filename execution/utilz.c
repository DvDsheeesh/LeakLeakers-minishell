/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:52:22 by halbit            #+#    #+#             */
/*   Updated: 2026/06/22 19:16:50 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->var);
		free(env->value);
		free(env);
		env = tmp;
	}
}

t_env	*env_copy(char **envp)
{
	t_env	*head;
	t_env	*cur;
	t_env	*node;
	char	*eq;
	int		i;

	if (!envp || !envp[0])
		return (NULL);
	head = NULL;
	cur = NULL;
	i = 0;
	while (envp[i])
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return (head);
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			node->var = ft_substr(envp[i], 0, eq - envp[i]);
			node->value = ft_strdup(eq + 1);
		}
		else
		{
			node->var = ft_strdup(envp[i]);
			node->value = NULL;
		}
		node->next = NULL;
		if (!head)
			head = node;
		else
			cur->next = node;
		cur = node;
		i++;
	}
	return (head);
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
	{
		tmp = ft_strjoin(cur->var, "=");
		arr[i] = ft_strjoin(tmp, cur->value ? cur->value : "");
		free(tmp);
		cur = cur->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		free(redirs->file);
		free(redirs);
		redirs = tmp;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_arr(cmds->command_args);
		free_redirs(cmds->redirs);
		if (cmds->infile != -1)
			close(cmds->infile);
		if (cmds->outfile != -1)
			close(cmds->outfile);
		free(cmds);
		cmds = tmp;
	}
}

int	open_redirections(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*r;
	int		fd;

	cmd = cmds;
	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == REDIR_IN)
			{
				fd = open(r->file, O_RDONLY);
				if (fd == -1)
					return (perror(r->file), 1);
				if (cmd->infile != -1)
					close(cmd->infile);
				cmd->infile = fd;
			}
			else if (r->type == REDIR_OUT)
			{
				fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
					return (perror(r->file), 1);
				if (cmd->outfile != -1)
					close(cmd->outfile);
				cmd->outfile = fd;
			}
			else if (r->type == REDIR_APPEND)
			{
				fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1)
					return (perror(r->file), 1);
				if (cmd->outfile != -1)
					close(cmd->outfile);
				cmd->outfile = fd;
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

void	sort_str_arr(char **arr, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strncmp(arr[i], arr[j], 4096) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}