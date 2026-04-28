/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_program_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:13 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 21:49:51 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_expanded_quotes(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
			(*str)[i] = 29;
		if ((*str)[i] == '\"')
			(*str)[i] = 30;
		i++;
	}
}

void	initialize_replacement_info(struct s_program_info *program, char *str,
		int prefix_len, int expand_to_exit_status)
{
	program->rep->original = alloc_handling(ft_strdup(str), program);
	if (expand_to_exit_status)
		program->rep->value = alloc_handling(ft_itoa(program->exit_status),
				program);
	else
		program->rep->value = alloc_handling(get_env_var_value
				(program->expander->var_name,
					program->env_list), program);
	replace_expanded_quotes(&program->rep->value);
	program->rep->prefix = alloc_handling(ft_substr(str, 0, prefix_len),
			program);
}

void	initialize_expander_info(struct s_program_info *program, char *str,
		int ignore_single_quotes)
{
	program->expander->original_str = alloc_handling(ft_strdup(str), program);
	program->expander->original_len = ft_strlen(str);
	program->expander->var_name = ft_calloc(ft_strlen(str) + 1, 1);
	alloc_handling(program->expander->var_name, program);
	program->expander->expanded_str = get_expanded_string(program,
			&program->expander->original_str, ignore_single_quotes);
}
