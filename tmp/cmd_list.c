/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:51:00 by melshata          #+#    #+#             */
/*   Updated: 2026/06/13 12:09:50 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Allocates and zero-initialises a new t_cmd */
static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->heredoc = NULL;
	cmd->append = 0;
	return (cmd);
}

/* Appends one string to cmd->args (reallocs the array) */
static void	add_arg(t_cmd *cmd, char *token)
{
	int		l;
	char	**new_args;
	int		i;

	l = arr_len(cmd->args) + 2;
	new_args = malloc(sizeof(char *) * l);
	if (!new_args)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i++] = ms_cpy(token);
	new_args[i] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

/*
** Checks whether a token is a redirect operator.
** If it is, consumes it and the next token (the filename),
** fills the appropriate t_cmd field, and advances *i by 2.
** Returns 1 if handled, 0 otherwise.
*/
static int	handle_redirect(t_cmd *cmd, char **tokens, int *i)
{
	char	*op;
	char	*target;

	op = tokens[*i];
	if (!tokens[*i + 1])
		return (0);
	target = tokens[*i + 1];
	if (ft_strncmp(op, "<<", 3) == 0)
	{
		free(cmd->heredoc);
		cmd->heredoc = ms_cpy(target);
	}
	else if (ft_strncmp(op, ">>", 3) == 0)
	{
		free(cmd->outfile);
		cmd->outfile = ms_cpy(target);
		cmd->append = 1;
	}
	else if (ft_strncmp(op, ">", 2) == 0)
	{
		free(cmd->outfile);
		cmd->outfile = ms_cpy(target);
		cmd->append = 0;
	}
	else if (ft_strncmp(op, "<", 2) == 0)
	{
		free(cmd->infile);
		cmd->infile = ms_cpy(target);
	}
	else
		return (0);
	*i += 2;
	return (1);
}

/*
** build_cmd_list() — converts flat token array into a t_list of t_cmd.
**
** Each pipe "|" ends the current command and starts a new one.
** Redirect tokens (<, >, <<, >>) consume the next token as filename.
** Everything else becomes an argument in cmd->args.
**
** Example:
**   tokens = ["cat", "<", "in.txt", "|", "grep", "foo", ">", "out.txt"]
**
**   cmd_list node 0: args=["cat"], infile="in.txt"
**   cmd_list node 1: args=["grep","foo"], outfile="out.txt"
*/
t_list	*build_cmd_list(char **tokens)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	int		i;

	if (!tokens)
		return (NULL);
	cmd_list = NULL;
	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
			cmd = new_cmd();
			if (!cmd)
				return (cmd_list);
			i++;
		}
		else if (!handle_redirect(cmd, tokens, &i))
		{
			add_arg(cmd, tokens[i]);
			i++;
		}
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	return (cmd_list);
}
