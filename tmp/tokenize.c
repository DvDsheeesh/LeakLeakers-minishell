/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:51:00 by melshata          #+#    #+#             */
/*   Updated: 2026/06/13 12:37:32 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Appends *word to token array, resets *word to NULL.
** Returns the new array, or NULL on alloc failure.
*/
static char	**flush_word(char **tokens, char **word)
{
	int		l;
	char	**new_arr;
	int		i;

	if (!*word)
		return (tokens);
	l = arr_len(tokens) + 2;
	new_arr = malloc(sizeof(char *) * l);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (tokens && tokens[i])
	{
		new_arr[i] = tokens[i];
		i++;
	}
	new_arr[i++] = *word;
	new_arr[i] = NULL;
	free(tokens);
	*word = NULL;
	return (new_arr);
}

/*
** Reads characters inside quotes (single or double).
** Appends each char to *word. Advances and returns new index
** pointing just past the closing quote.
*/
static int	read_quoted(char **word, char *line, int i, char quote)
{
	i++;
	while (line[i] && line[i] != quote)
	{
		*word = extend_str(*word, line[i]);
		i++;
	}
	if (line[i] == quote)
		i++;
	return (i);
}

/*
** Handles <, >, | operators.
** Flushes any current word first, then builds the operator
** as its own token (supports << and >>), flushes it too.
** Returns new index after the operator.
*/
static int	read_operator(char **tokens_ptr[], char *line, int i)
{
	char	**tokens;
	char	**word;
	char	op;

	tokens = tokens_ptr[0];
	word = tokens_ptr[1];
	op = line[i];
	tokens = flush_word(tokens, word);
	*word = extend_str(*word, op);
	i++;
	if ((op == '<' || op == '>') && line[i] == op)
	{
		*word = extend_str(*word, op);
		i++;
	}
	tokens = flush_word(tokens, word);
	tokens_ptr[0] = tokens;
	return (i);
}

/*
** tokenize() — main entry point.
**
** Converts a raw input line into a flat NULL-terminated array of tokens:
**   "ls -la | grep foo"  ->  ["ls", "-la", "|", "grep", "foo", NULL]
**   "cat < in >> out"    ->  ["cat", "<", "in", ">>", "out", NULL]
**   "echo \"hi there\""  ->  ["echo", "hi there", NULL]
**
** Rules:
**   - Quoted content (single or double) is one token, quotes stripped.
**   - |, <, >, <<, >> each become their own token.
**   - Whitespace separates tokens (outside quotes).
*/
char	**tokenize(char *line)
{
	char	**tokens;
	char	*word;
	char	*ptrs[2];
	int		i;

	tokens = NULL;
	word = NULL;
	i = 0;
	while (line && line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = read_quoted(&word, line, i, line[i]);
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			ptrs[0] = (char *)&tokens;
			ptrs[1] = (char *)&word;
			i = read_operator((char ***)ptrs, line, i);
		}
		else if (line[i] == ' ' || line[i] == '\t')
		{
			tokens = flush_word(tokens, &word);
			i++;
		}
		else
		{
			word = extend_str(word, line[i]);
			i++;
		}
	}
	tokens = flush_word(tokens, &word);
	return (tokens);
}
