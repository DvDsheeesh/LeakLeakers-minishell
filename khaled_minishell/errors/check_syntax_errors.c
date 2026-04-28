/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:02 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/24 03:45:36 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_syntax_error(char *str, struct s_program_info *program)
{
	write(2, "-ShellWeDance: syntax error near unexpected token `", 48);
	write(2, str, ft_strlen(str));
	write(2, "\'\n", 2);
	program->exit_status = 2;
	return (0);
}

int	check_syntax_errors(struct s_tokens *tokens_list,
		struct s_program_info *program)
{
	while (tokens_list)
	{
		if (tokens_list->type != TOKEN_WORD && tokens_list->type != TOKEN_PIPE)
		{
			if (!tokens_list->next)
				return (handle_syntax_error("newline", program));
			else if (tokens_list->next->type != TOKEN_WORD)
				return (handle_syntax_error(tokens_list->next->content,
						program));
		}
		else if (tokens_list->type == TOKEN_PIPE)
		{
			if (!tokens_list->next || !tokens_list->previous)
				return (handle_syntax_error("|", program));
			else if (tokens_list->next->type == TOKEN_PIPE)
				return (handle_syntax_error("|", program));
		}
		tokens_list = tokens_list->next;
	}
	return (1);
}

int	check_unclosed_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!ft_strchr(str + i + 1, str[i]))
			{
				write(2, "-ShellWeDance: syntax error unclosed quotes\n",
					ft_strlen("-ShellWeDance: syntax error unclosed quotes\n"));
				return (0);
			}
			i = ft_strchr(str + i + 1, str[i]) - str + 1;
		}
		else
			i++;
	}
	return (1);
}
