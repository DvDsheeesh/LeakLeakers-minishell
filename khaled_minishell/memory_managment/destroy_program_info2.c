/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_program_info2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:11 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 20:25:11 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	files_list_destroy(struct s_redirections_files *files_list)
{
	struct s_redirections_files	*tmp;

	while (files_list)
	{
		tmp = files_list;
		files_list = files_list->next;
		free(tmp->name);
		free(tmp);
	}
}

void	destroy_replacement_info(struct s_replacement_info *rep)
{
	if (rep->original)
		free(rep->original);
	if (rep->prefix)
		free(rep->prefix);
	if (rep->value)
		free(rep->value);
	free(rep);
}

void	destroy_expander_info(struct s_expander_info *expander)
{
	if (expander->original_str)
		free(expander->original_str);
	if (expander->var_name)
		free(expander->var_name);
	if (expander->expanded_str)
		free(expander->expanded_str);
	ft_memset(expander, 0, sizeof(struct s_expander_info));
	free(expander);
}
