/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:36 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 20:25:37 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_tokens_types(struct s_tokens **tokens_list)
{
	struct s_tokens	*tmp;

	tmp = *tokens_list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "|", 1) && ft_strlen(tmp->content) == 1)
			tmp->type = TOKEN_PIPE;
		else if (!ft_strncmp(tmp->content, "<", 1)
			&& ft_strlen(tmp->content) == 1)
			tmp->type = TOKEN_REDIR_INPUT;
		else if (!ft_strncmp(tmp->content, ">", 1)
			&& ft_strlen(tmp->content) == 1)
			tmp->type = TOKEN_REDIR_OUTPUT;
		else if (!ft_strncmp(tmp->content, ">>", 2)
			&& ft_strlen(tmp->content) == 2)
			tmp->type = TOKEN_REDIR_APPEND;
		else if (!ft_strncmp(tmp->content, "<<", 2)
			&& ft_strlen(tmp->content) == 2)
			tmp->type = TOKEN_HEREDOC;
		else
			tmp->type = TOKEN_WORD;
		tmp = tmp->next;
	}
}

void	assign_tokens_words(struct s_program_info *program, int *i, char *str,
		struct s_tokens **new_node)
{
	int		j;
	char	*content;

	j = 0;
	while (str[*i + j] && !ft_strchr(" <>|", str[*i + j]))
	{
		if (str[*i + j] == '\"' || str[*i + j] == '\'')
			j += ft_strchr(str + *i + j + 1, str[*i + j]) - (str + j + *i) + 1;
		else
			j++;
	}
	content = alloc_handling(ft_substr(str, *i, j), program);
	*new_node = tokens_list_new_node(content);
	if (!(*new_node))
	{
		free(content);
		alloc_handling(NULL, program);
	}
	*i += j;
}

void	assign_tokens_redirections_pipes(struct s_program_info *program, int *i,
		char *str, struct s_tokens **new_node)
{
	char	*content;

	if (str[*i] == str[*i + 1] && str[*i] != '|')
	{
		content = alloc_handling(ft_substr(str, *i, 2), program);
		*new_node = tokens_list_new_node(content);
		(*i) += 2;
	}
	else
	{
		content = alloc_handling(ft_substr(str, *i, 1), program);
		*new_node = tokens_list_new_node(content);
		(*i)++;
	}
	if (!(*new_node))
	{
		free(content);
		alloc_handling(NULL, program);
	}
}

void	assign_tokens_content(struct s_program_info *program, char *str)
{
	struct s_tokens	*new_node;
	int				i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				assign_tokens_redirections_pipes(program, &i, str, &new_node);
			else
				assign_tokens_words(program, &i, str, &new_node);
			tokens_list_add_back(&program->tokens_list, new_node);
		}
	}
}
