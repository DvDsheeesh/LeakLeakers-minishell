/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 23:48:21 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 10:32:54 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**special_symbols_parse(char **arg_arr, char *line,
	char **word, int *i)
{
	char	**new_arr;

	if (*word)
		arg_arr = add_arg_to_arr(arg_arr, word, 1, 1);
	*word = ms_extend(*word, line[*i]);
	if (line[(*i) + 1] == line[*i]
		&& (line[*i] == '<' || line[*i] == '>'))
		*word = ms_extend(*word, line[(*i)++]);
	new_arr = add_arg_to_arr(arg_arr, word, 1, 1);
	return (new_arr);
}

static int	is_var_name(char *mline, int i)
{
	return (ft_isalnum(mline[i + 1]) || mline[i + 1] == '_'
		|| mline[i + 1] == '?');
}

static int	dispatch_char(char **mline, int *i, t_info *vars, char ***arg_arr)
{
	if ((*mline)[*i] == '\'')
		*i = join_arg(&(vars->word), *mline, *i + 1, '\'');
	else if ((*mline)[*i] == '"')
		*i = join_arg_dq(&(vars->word), mline, vars, *i + 1);
	else if ((*mline)[*i] == '$' && (*mline)[*i + 1] != '$'
		&& is_var_name(*mline, *i))
	{
		*i = dollar_of_truth(mline, vars, *i);
		return (1);
	}
	else if ((*mline)[*i] == '<' || (*mline)[*i] == '>' || (*mline)[*i] == '|')
		*arg_arr = special_symbols_parse(*arg_arr, *mline, &(vars->word), i);
	else if (ft_isprint((*mline)[*i]) && (*mline)[*i] != ' '
		&& (*mline)[*i] != '\t')
		vars->word = ms_extend(vars->word, (*mline)[*i]);
	return (0);
}

static char	**finalize_word(char **arg_arr, char *mline, int i, t_info *vars)
{
	if ((mline[i] == ' ' || mline[i] == '\t' || mline[i + 1] == '\0')
		&& vars->word)
		arg_arr = add_arg_to_arr(arg_arr, &(vars->word), 1, 1);
	return (arg_arr);
}

char	**split_input_words(char *line, t_info *vars)
{
	char	*mline;
	int		i;
	char	**arg_arr;

	mline = ft_strdup(line);
	if (!mline)
		return (NULL);
	i = 0;
	arg_arr = NULL;
	while (mline && mline[i])
	{
		if (dispatch_char(&mline, &i, vars, &arg_arr))
			continue ;
		arg_arr = finalize_word(arg_arr, mline, i, vars);
		i++;
	}
	free(mline);
	return (arg_arr);
}
