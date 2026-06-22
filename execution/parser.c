/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 21:08:40 by halbit            #+#    #+#             */
/*   Updated: 2026/06/22 19:16:47 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**split_args(char *seg)
{
	char	**args;

	if (!seg || !*seg)
		return (NULL);
	args = ft_split(seg, ' ');
	if (args && !args[0])
		return (free_arr(args), NULL);
	return (args);
}

static char	*next_seg(char **line)
{
	char	*pipe;
	char	*raw;
	char	*seg;
	size_t	len;

	pipe = ft_strchr(*line, '|');
	if (pipe)
		len = (size_t)(pipe - *line);
	else
		len = ft_strlen(*line);
	raw = ft_substr(*line, 0, len);
	if (pipe)
		*line = pipe + 1;
	else
		*line = *line + len;
	if (!raw)
		return (NULL);
	seg = ft_strtrim(raw, " \t");
	free(raw);
	return (seg);
}

static t_cmd	*parse_segment(char *seg)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->command_args = split_args(seg);
	node->infile = -1;
	node->outfile = -1;
	node->next = NULL;
	if (!node->command_args)
		return (free(node), NULL);
	return (node);
}

t_cmd	*parse_line(char *line)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*node;
	char	*seg;

	if (!line || !*line)
		return (NULL);
	head = NULL;
	tail = NULL;
	while (*line)
	{
		seg = next_seg(&line);
		if (!seg)
			continue ;
		node = parse_segment(seg);
		free(seg);
		if (!node)
			continue ;
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
	}
	return (head);
}
