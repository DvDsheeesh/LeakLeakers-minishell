/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilz2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 08:36:37 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 10:29:33 by melshata         ###   ########.fr       */
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

static void	free_redirs(t_redir *redirs)
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

int	exit_child(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
	else if (WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	return (128 + WTERMSIG(status));
}
