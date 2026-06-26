/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 23:39:10 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 10:30:31 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_redir(t_redir **head, t_redir *r)
{
	t_redir	*cur;

	if (!r)
		return ;
	if (!*head)
	{
		*head = r;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = r;
}

static int	command_looping(char **arr, t_cmd *last, int i)
{
	if (ft_strncmp(arr[i], "|", 2) == 0)
		last->next = create_command_node();
	else if (ft_strncmp(arr[i], "<<", 3) == 0 && arr[i + 1])
		append_redir(&last->redirs, new_redir(REDIR_HEREDOC, arr[++i]));
	else if (ft_strncmp(arr[i], "<", 2) == 0 && arr[i + 1])
		append_redir(&last->redirs, new_redir(REDIR_IN, arr[++i]));
	else if (ft_strncmp(arr[i], ">>", 3) == 0 && arr[i + 1])
		append_redir(&last->redirs, new_redir(REDIR_APPEND, arr[++i]));
	else if (ft_strncmp(arr[i], ">", 2) == 0 && arr[i + 1])
		append_redir(&last->redirs, new_redir(REDIR_OUT, arr[++i]));
	else
		last->command_args = add_arg_to_arr(
				last->command_args, &arr[i], 1, 0);
	return (i);
}

static t_cmd	*parsing_commands(t_info *vars)
{
	t_cmd		*head;
	t_cmd		*last;
	char		**arr;
	int			i;

	head = create_command_node();
	arr = vars->arg_arr;
	i = 0;
	while (arr && arr[i])
	{
		last = last_command(head);
		i = command_looping(arr, last, i);
		i++;
	}
	return (head);
}

int	command_process(t_info *vars)
{
	t_cmd	*cmd;

	cmd = parsing_commands(vars);
	vars->cmds_head = cmd;
	if (open_redirections(cmd, vars))
	{
		free_cmds(cmd);
		return (1);
	}
	setup_execution_signals();
	vars->exit_status = execute(cmd, vars);
	free_cmds(cmd);
	setup_inline_signals();
	return (vars->exit_status);
}
