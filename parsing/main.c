/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 23:36:14 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 10:32:27 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

static void	main_loop(char **line, t_info *vars)
{
	setup_inline_signals();
	*line = readline("minishell$");
	if (g_signal)
	{
		vars->exit_status = g_signal;
		g_signal = 0;
	}
	if (*line && (*line[0] == '\0'))
		return ;
	if (*line == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free_vars(vars);
		exit(0);
	}
	if (*line && (*line)[0])
		add_history(*line);
	reset_vars(vars);
	vars->line = *line;
	vars->arg_arr = split_input_words(*line, vars);
	vars->label_arr = labelizing(vars);
	if (validate_label(vars))
		command_process(vars);
}

int	main(int ac, char **av, char **env)
{
	t_info	*vars;
	char	*line;

	(void)ac;
	(void)av;
	g_signal = 0;
	vars = vars_init(NULL, env);
	if (!vars)
		return (1);
	while (1)
		main_loop(&line, vars);
	return (0);
}
