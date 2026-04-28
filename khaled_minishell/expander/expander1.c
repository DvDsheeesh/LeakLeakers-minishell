/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:24:16 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 21:45:33 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_var_name_with_value(struct s_program_info *program, char *str,
		int *i, int j)
{
	char	*tmp;

	tmp = program->rep->prefix;
	program->rep->prefix = alloc_handling(ft_strjoin(program->rep->prefix,
				program->rep->value), program);
	free(tmp);
	tmp = program->rep->original;
	program->rep->original = alloc_handling(ft_substr(str, *i, ft_strlen(str)
				- *i), program);
	free(tmp);
	tmp = program->rep->original;
	program->rep->original = alloc_handling(ft_strjoin(program->rep->prefix,
				program->rep->original), program);
	*i = *i + ft_strlen(program->rep->value) - j - 2;
	free(tmp);
	tmp = alloc_handling(ft_strdup(program->rep->original), program);
	destroy_replacement_info(program->rep);
	program->rep = NULL;
	return (tmp);
}

int	determine_expansion_type(struct s_program_info *program, char **str, int *i,
		int ignore_quotes)
{
	int		j;
	char	*tmp;

	j = 0;
	if (((*str)[*i] == '\"' || (*str)[*i] == '\'') && !ignore_quotes)
		return (expand_quotes(program, str, i));
	if ((*str)[*i] == '?')
		return (expand_to_exit_status(program, str, i));
	if (!ft_isalpha((*str)[*i]) && !((*str)[(*i)] == '_'))
		return (1);
	while (ft_isalpha((*str)[(*i)]) || ft_isdigit((*str)[*i])
		|| (*str)[*i] == '_')
		program->expander->var_name[j++] = (*str)[(*i)++];
	program->expander->var_name[j] = '\0';
	program->rep = alloc_handling(ft_calloc(1,
				sizeof(struct s_replacement_info)), program);
	initialize_replacement_info(program, *str, *i - j - 1, 0);
	tmp = *str;
	*str = replace_var_name_with_value(program, *str, i, j);
	free(tmp);
	return (1);
}

char	*get_expanded_string(struct s_program_info *program, char **str,
		int ignore_single_quotes)
{
	int	i;
	int	inside_double_quotes;

	i = 0;
	inside_double_quotes = 0;
	while ((*str)[i])
	{
		ft_memset(program->expander->var_name, 0,
			program->expander->original_len + 1);
		if ((*str)[i] == '\'' && !inside_double_quotes
			&& ignore_single_quotes == 0)
			i = ft_strchr(*str + i + 1, '\'') - *str;
		else if ((*str)[i] == '$' && (*str)[i + 1])
		{
			i++;
			determine_expansion_type(program, str, &i, ignore_single_quotes);
		}
		else if ((*str)[i] == '\"')
			inside_double_quotes = !inside_double_quotes;
		i++;
	}
	return (alloc_handling(ft_strdup(*str), program));
}

void	expand_tokens(struct s_program_info *program)
{
	char			*tmp;
	struct s_tokens	*token;

	token = program->tokens_list;
	while (token)
	{
		if (((token->previous && token->previous->type != TOKEN_HEREDOC)
				|| (!token->previous)) && token->type == TOKEN_WORD)
		{
			program->expander = alloc_handling(
					ft_calloc(sizeof(struct s_expander_info), 1), program);
			initialize_expander_info(program, token->content, 0);
			tmp = token->content;
			token->content = alloc_handling(
					ft_strdup(program->expander->expanded_str), program);
			free(tmp);
			destroy_expander_info(program->expander);
			program->expander = NULL;
		}
		token = token->next;
	}
}
