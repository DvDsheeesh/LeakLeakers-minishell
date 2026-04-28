/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:24:19 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 20:24:20 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_quotes(struct s_program_info *program, char **str, int *i)
{
	char	*new_string;
	char	*tmp;
	int		j;
	int		k;

	j = 0;
	new_string = alloc_handling(ft_calloc(ft_strlen(*str) + 1, 1), program);
	while (j < (*i) - 1)
	{
		new_string[j] = (*str)[j];
		j++;
	}
	k = 0;
	while ((*str)[(*i) + k])
	{
		new_string[j++] = (*str)[(*i) + k];
		k++;
	}
	(*i) -= 2;
	tmp = *str;
	*str = new_string;
	free(tmp);
	return (1);
}

int	expand_to_exit_status(struct s_program_info *program, char **str, int *i)
{
	char	*tmp;

	(*i) += 1;
	program->rep = alloc_handling(ft_calloc(1,
				sizeof(struct s_replacement_info)), program);
	initialize_replacement_info(program, *str, *i - 2, 1);
	tmp = *str;
	*str = replace_var_name_with_value(program, *str, i, 1);
	free(tmp);
	return (1);
}
