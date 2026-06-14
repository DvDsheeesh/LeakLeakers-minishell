/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 21:08:40 by halbit            #+#    #+#             */
/*   Updated: 2026/06/14 20:15:48 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int	count_args(char *line)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*line)
	{
		if (!is_space(*line))
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		line++;
	}
	return (count);
}

static char	*next_arg(char **line)
{
	char	*start;

	while (**line && is_space(**line))
		(*line)++;
	if (!**line)
		return (NULL);
	start = *line;
	while (**line && !is_space(**line))
		(*line)++;
	return (ft_substr(start, 0, *line - start));
}

static char	**split_args(char *line)
{
	int		n;
	char	**args;
	int		i;

	n = count_args(line);
	if (!n)
		return (NULL);
	args = malloc(sizeof(char *) * (n + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (i < n)
	{
		args[i] = next_arg(&line);
		if (!args[i])
			return (free_arr(args), NULL);
		i++;
	}
	args[n] = NULL;
	return (args);
}

t_cmd	*parse_line(char *line)
{
	t_cmd	*cmd;

	if (!line || !*line)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->command_args = split_args(line);
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->next = NULL;
	if (!cmd->command_args)
		return (free(cmd), NULL);
	return (cmd);
}
