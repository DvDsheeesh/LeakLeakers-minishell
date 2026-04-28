/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:18 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 21:50:38 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_heredoc_line(char *limiter, char **line)
{
	*line = readline("> ");
	if (g_sig_status == 130 || !(*line))
	{
		if (*line)
			free(*line);
		return (1);
	}
	if (!ft_strncmp(*line, limiter, ft_strlen(limiter) + 1))
	{
		free(*line);
		return (1);
	}
	return (0);
}

void	read_heredoc_not_infile(char *limiter, struct s_program_info *program)
{
	char	*line;
	int		fd_stdin;

	fd_stdin = handle_syserror(dup(STDIN_FILENO), program);
	setup_heredoc_signals();
	while (1)
	{
		if (read_heredoc_line(limiter, &line))
			break ;
		free(line);
	}
	if (dup2(fd_stdin, STDIN_FILENO) == -1)
	{
		close(fd_stdin);
		handle_syserror(-1, program);
	}
	close(fd_stdin);
	setup_interactive_signals();
}

void	expand_heredoc_line(struct s_program_info *program, int fd[2],
		char **line)
{
	char	*tmp;

	tmp = *line;
	program->expander = ft_calloc(1, sizeof(struct s_expander_info));
	if (!program->expander)
		handle_heredoc_error(program, fd, *line, -1);
	initialize_expander_info(program, *line, 1);
	*line = ft_strdup(program->expander->expanded_str);
	free(tmp);
	if (!(*line))
		handle_heredoc_error(program, fd, *line, -1);
	destroy_expander_info(program->expander);
	program->expander = NULL;
}

int	read_heredoc_infile(char *limiter, struct s_program_info *program,
		int expand_heredoc_content)
{
	char	*line;
	int		fd[2];
	int		fd_stdin;

	handle_syserror(pipe(fd), program);
	fd_stdin = dup(STDIN_FILENO);
	if (fd_stdin == -1)
		handle_heredoc_error(program, fd, NULL, -1);
	setup_heredoc_signals();
	while (1)
	{
		if (read_heredoc_line(limiter, &line))
			break ;
		if (expand_heredoc_content)
			expand_heredoc_line(program, fd, &line);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	if (dup2(fd_stdin, STDIN_FILENO) == -1)
		handle_heredoc_error(program, fd, NULL, fd_stdin);
	close(fd_stdin);
	setup_interactive_signals();
	close(fd[1]);
	return (fd[0]);
}

void	parse_heredoc(struct s_tokens *token, struct s_commands *new_command,
		struct s_program_info *program)
{
	int		expand_heredoc_content;
	char	*tmp;

	if (g_sig_status == 130)
		return ;
	expand_heredoc_content = !(ft_strchr(token->content, '\'')
			|| ft_strchr(token->content, '\"'));
	tmp = token->content;
	token->content = remove_quotes_from_token(program, token);
	free(tmp);
	if (heredoc_is_infile(token))
		new_command->heredoc_fd = read_heredoc_infile(token->content, program,
				expand_heredoc_content);
	else
		read_heredoc_not_infile(token->content, program);
}
