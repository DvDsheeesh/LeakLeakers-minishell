/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_program_info1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:08 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 20:25:08 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_two_dimensional(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	commands_list_destroy(struct s_commands *commands_list)
{
	struct s_commands	*tmp;

	while (commands_list)
	{
		tmp = commands_list;
		commands_list = commands_list->next;
		command_destroy(tmp);
	}
}

void	tokens_list_destroy(struct s_tokens *tokens_list)
{
	struct s_tokens	*tmp;

	while (tokens_list)
	{
		tmp = tokens_list;
		tokens_list = tokens_list->next;
		free(tmp->content);
		free(tmp);
	}
}

void	env_list_destroy(struct s_env *env_list)
{
	struct s_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

void	destroy_program_info(struct s_program_info *program)
{
	if (program->tokens_list)
		tokens_list_destroy(program->tokens_list);
	if (program->env_list)
		env_list_destroy(program->env_list);
	if (program->expander)
		destroy_expander_info(program->expander);
	if (program->rep)
		destroy_replacement_info(program->rep);
	if (program->command_list)
		commands_list_destroy(program->command_list);
	if (program->orig_in != -1)
		close(program->orig_in);
	if (program->orig_out != -1)
		close(program->orig_out);
}
