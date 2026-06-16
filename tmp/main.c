/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:51:00 by melshata          #+#    #+#             */
/*   Updated: 2026/06/13 12:09:51 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Initialises t_vars at startup.
** env list is built once from envp and kept for the shell's lifetime.
*/
static void	init_vars(t_vars *v, char **env)
{
	v->env = extract_env(env);
	v->cmd_list = NULL;
	v->line = NULL;
	v->tokens = NULL;
	v->exit_status = 0;
}

/*
** One iteration of the REPL:
**   1. readline  -> v->line
**   2. tokenize  -> v->tokens
**   3. build_cmd_list -> v->cmd_list
**   4. (execute  -> coming next)
**   5. free everything except v->env
*/
static void	run_loop(t_vars *v)
{
	v->line = readline("minishell> ");
	if (!v->line)
	{
		printf("exit\n");
		exit(v->exit_status);
	}
	if (v->line[0])
		add_history(v->line);
	v->tokens = tokenize(v->line);
	v->cmd_list = build_cmd_list(v->tokens);
	/* --- DEBUG: remove before submission --- */
	print_tokens(v->tokens);
	print_cmd_list(v->cmd_list);
	/* --------------------------------------- */

	/* TODO: execute(v); */

	free_vars(v);
}

int	main(int ac, char **av, char **env)
{
	t_vars	v;

	(void)ac;
	(void)av;
	init_vars(&v, env);
	while (1)
		run_loop(&v);
	return (0);
}
