/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:20 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 20:25:21 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_is_infile(struct s_tokens *token)
{
	int	is_infile;

	is_infile = 1;
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_HEREDOC || token->type == TOKEN_REDIR_INPUT)
		{
			is_infile = 0;
			break ;
		}
		token = token->next;
	}
	return (is_infile);
}

void	handle_heredoc_error(struct s_program_info *program, int fd[2],
		char *line, int fd_stdin)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (fd_stdin != -1)
		close(fd_stdin);
	if (line)
		free(line);
	alloc_handling(NULL, program);
}
