/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:22 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 21:47:28 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_command_args(struct s_tokens *token)
{
	int	count;

	count = 0;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
			if (!token->previous || token->previous->type == TOKEN_WORD
				|| token->previous->type == TOKEN_PIPE)
				count++;
		token = token->next;
	}
	return (count);
}

int	get_file_type(enum e_token_type type)
{
	if (type == TOKEN_REDIR_OUTPUT)
		return (OUTFILE_TRUNCATE);
	if (type == TOKEN_REDIR_APPEND)
		return (OUTFILE_APPEND);
	if (type == TOKEN_REDIR_INPUT)
		return (INFILE);
	return (-1);
}

void	parse_redirections(struct s_tokens *token,
		struct s_commands *new_command, struct s_program_info *program)
{
	struct s_redirections_files	*new_file;
	char						*file_name;
	int							file_type;

	if (token->previous->type >= TOKEN_REDIR_OUTPUT
		&& token->previous->type <= TOKEN_REDIR_INPUT)
	{
		file_type = get_file_type(token->previous->type);
		file_name = alloc_handling(ft_strdup(token->content), program);
		new_file = files_list_new_node(file_name, file_type);
		if (!new_file)
		{
			free(file_name);
			alloc_handling(NULL, program);
		}
		files_list_add_back(&new_command->files_list, new_file);
	}
	else if (token->previous->type == TOKEN_HEREDOC)
		parse_heredoc(token, new_command, program);
}

void	parser(struct s_program_info *program)
{
	struct s_tokens		*token;
	struct s_commands	*new_command;
	int					i;

	token = program->tokens_list;
	while (token)
	{
		i = 0;
		new_command = alloc_handling(commands_list_new_node(), program);
		commands_list_add_back(&program->command_list, new_command);
		new_command->command_args = alloc_handling(ft_calloc(count_command_args
					(token) + 1, sizeof(char *)), program);
		while (token && token->type != TOKEN_PIPE)
		{
			if (token->type == TOKEN_WORD && token->previous
				&& (token->previous->type >= 1 && token->previous->type <= 4))
				parse_redirections(token, new_command, program);
			else if (token->type == TOKEN_WORD)
				new_command->command_args[i++] = alloc_handling(
						ft_strdup(token->content), program);
			token = token->next;
		}
		if (token)
			token = token->next;
	}
}
