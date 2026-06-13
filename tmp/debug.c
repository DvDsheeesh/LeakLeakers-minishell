/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:51:00 by melshata          #+#    #+#             */
/*   Updated: 2026/06/13 12:40:23 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* !! REMOVE THIS FILE BEFORE FINAL SUBMISSION !! */

#include "minishell.h"

/* Prints the flat token array produced by tokenize() */
void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	printf("=== TOKENS ===\n");
	while (tokens && tokens[i])
	{
		printf("  [%d] \"%s\"\n", i, tokens[i]);
		i++;
	}
	printf("==============\n");
}

/* Prints each t_cmd node in the cmd_list */
void	print_cmd_list(t_list *cmd_list)
{
	t_list	*node;
	t_cmd	*cmd;
	int		cmd_num;
	int		j;

	node = cmd_list;
	cmd_num = 0;
	printf("=== CMD LIST ===\n");
	while (node)
	{
		cmd = (t_cmd *)node->content;
		printf("--- CMD [%d] ---\n", cmd_num++);
		j = 0;
		while (cmd->args && cmd->args[j])
		{
			printf("  arg[%d]: \"%s\"\n", j, cmd->args[j]);
			j++;
		}
		if (cmd->infile)
			printf("  infile : \"%s\"\n", cmd->infile);
		if (cmd->outfile)
			printf("  outfile: \"%s\" (append=%d)\n", cmd->outfile, cmd->append);
		if (cmd->heredoc)
			printf("  heredoc: \"%s\"\n", cmd->heredoc);
		node = node->next;
	}
	printf("================\n");
}
