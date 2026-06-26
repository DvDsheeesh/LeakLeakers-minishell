/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 09:05:47 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 17:06:48 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_vars(t_info *vars)
{
	if (vars)
	{
		if (vars->env)
			free_env(vars->env);
		vars->env = NULL;
		if (vars->arg_arr)
			free_arr(vars->arg_arr);
		vars->arg_arr = NULL;
		if (vars->label_arr)
			free(vars->label_arr);
		vars->label_arr = NULL;
		if (vars->line)
			free(vars->line);
		vars->line = NULL;
		if (vars->word)
			free(vars->word);
		vars->word = NULL;
		free(vars);
	}
}

t_info	*vars_init(char *line, char **env)
{
	t_info	*vars;

	vars = malloc(sizeof(t_info));
	if (!vars)
		return (NULL);
	vars->env = extract_env(env);
	vars->arg_arr = NULL;
	vars->label_arr = NULL;
	vars->line = line;
	vars->word = NULL;
	vars->exit_status = 0;
	return (vars);
}

void	reset_vars(t_info *vars)
{
	free_arr(vars->arg_arr);
	vars->arg_arr = NULL;
	free(vars->label_arr);
	vars->label_arr = NULL;
	free(vars->word);
	vars->word = NULL;
	free(vars->line);
	vars->line = NULL;
}
