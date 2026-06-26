/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 23:58:52 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 20:04:51 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_arg_to_arr(char **arr, char **word,
	int free_old, int free_word)
{
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * (arr_len(arr) + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (arr && arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	if (word && *word)
	{
		new[i++] = ft_strdup(*word);
		if (free_word)
		{
			free(*word);
			*word = NULL;
		}
	}
	new[i] = NULL;
	if (free_old)
		free_arr(arr);
	return (new);
}

int	join_arg(char **word, char *line, int i, char end_char)
{
	while (line && line[i] && line[i] != end_char)
	{
		*word = ms_extend(*word, line[i]);
		i++;
	}
	if (line && line[i] != end_char)
		i--;
	return (i);
}

int	join_arg_dq(char **word, char **line, t_info *vars, int i)
{
	while ((*line)[i] && (*line)[i] != '"')
	{
		if ((*line)[i] == '$' && (*line)[i + 1] != '$'
			&& (ft_isalnum((unsigned char)(*line)[i + 1])
				|| (*line)[i + 1] == '_' || (*line)[i + 1] == '?'))
			i = dollar_of_truth(line, vars, i);
		else
		{
			*word = ms_extend(*word, (*line)[i]);
			i++;
		}
	}
	if ((*line) && (*line)[i] != '"')
		i--;
	return (i);
}
