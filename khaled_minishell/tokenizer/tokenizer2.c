/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:39 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 22:00:10 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	insert_expanded_token(struct s_program_info *program,
		struct s_tokens *token, struct s_tokens *new_token)
{
	if (token->previous)
		token->previous->next = new_token;
	new_token->next = token;
	new_token->type = TOKEN_WORD;
	if (token->previous)
		new_token->previous = token->previous;
	else
	{
		new_token->previous = NULL;
		program->tokens_list = new_token;
	}
	token->previous = new_token;
}

void	split_token_by_spaces(struct s_program_info *program,
		struct s_tokens *token, int i)
{
	char			*tmp;
	struct s_tokens	*new_token;
	int				j;

	j = 0;
	while (token->content[i + j] == ' ')
		j++;
	tmp = alloc_handling(ft_substr(token->content, 0, i), program);
	new_token = tokens_list_new_node(tmp);
	if (!new_token)
	{
		free(tmp);
		alloc_handling(NULL, program);
	}
	tmp = token->content;
	token->content = ft_substr(token->content, i + j, ft_strlen(token->content)
			- (i + j));
	free(tmp);
	if (!token->content)
	{
		free(new_token->content);
		free(new_token);
		alloc_handling(NULL, program);
	}
	insert_expanded_token(program, token, new_token);
}

void	split_unquoted_expansion(struct s_program_info *program)
{
	int				i;
	struct s_tokens	*token;

	token = program->tokens_list;
	while (token)
	{
		if (((token->previous && token->previous->type != TOKEN_HEREDOC)
				|| (!token->previous)) && token->type == TOKEN_WORD)
		{
			i = 0;
			while (token->content[i])
			{
				if (token->content[i] == '\'' || token->content[i] == '\"')
					i = ft_strchr(token->content + i + 1, token->content[i])
						- token->content;
				else if (token->content[i] == ' ')
				{
					split_token_by_spaces(program, token, i);
					i = -1;
				}
				i++;
			}
		}
		token = token->next;
	}
}
