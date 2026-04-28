/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:24:59 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 20:25:00 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct s_commands	*commands_list_new_node(void)
{
	struct s_commands	*node;

	node = ft_calloc(1, sizeof(struct s_commands));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->heredoc_fd = -1;
	return (node);
}

struct s_commands	*commands_list_last_node(struct s_commands *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	commands_list_add_back(struct s_commands **lst, struct s_commands *new)
{
	struct s_commands	*lastnode;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lastnode = commands_list_last_node(*lst);
	lastnode->next = new;
}

void	command_destroy(struct s_commands *command)
{
	if (command->absolute_path)
		free(command->absolute_path);
	if (command->command_args)
		free_two_dimensional(command->command_args);
	if (command->heredoc_fd != -1)
	{
		close(command->heredoc_fd);
		command->heredoc_fd = -1;
	}
	if (command->files_list)
		files_list_destroy(command->files_list);
	free(command);
}
