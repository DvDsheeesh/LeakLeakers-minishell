/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollaroze.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 23:49:16 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 10:31:07 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*replace_range(char *line, int start, int end, char *new_word)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = malloc(ft_strlen(line) + ft_strlen(new_word)
			- (end - start) + 1);
	if (!new_line)
		return (line);
	i = 0;
	while (i < start && line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	j = 0;
	while (new_word[j])
		new_line[i++] = new_word[j++];
	j = end;
	while (line[j])
		new_line[i++] = line[j++];
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

static int	dollar_exit(char **line, int start, t_info *vars)
{
	char	*code;

	code = ft_itoa(vars->exit_status);
	if (!code)
		return (start + 2);
	*line = replace_range(*line, start, start + 2, code);
	free(code);
	return (start);
}

int	dollar_of_truth(char **line, t_info *vars, int i)
{
	int		start;
	int		end;
	char	*var_name;
	char	*value;

	start = i++;
	if ((*line)[i] == '?')
		return (dollar_exit(line, start, vars));
	while ((*line)[i]
		&& (ft_isalnum((*line)[i]) || (*line)[i] == '_'))
		i++;
	end = i;
	if (end == start + 1)
		return (end);
	var_name = ft_substr(*line, start + 1, end - start - 1);
	if (!var_name)
		return (end);
	value = env_get(vars->env, var_name);
	free(var_name);
	if (!value)
		value = "";
	*line = replace_range(*line, start, end, value);
	return (start);
}
