/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:42 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/24 05:53:30 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_sig_status = 0;

void	clean_cycle(struct s_program_info *info)
{
	if (info->command_list)
	{
		commands_list_destroy(info->command_list);
		info->command_list = NULL;
	}
	if (info->tokens_list)
	{
		tokens_list_destroy(info->tokens_list);
		info->tokens_list = NULL;
	}
}

static void	handle_tokenization(struct s_program_info *info, char *line)
{
	assign_tokens_content(info, line);
	assign_tokens_types(&info->tokens_list);
	if (!check_syntax_errors(info->tokens_list, info))
	{
		info->exit_status = 2;
		return ;
	}
	expand_tokens(info);
	split_unquoted_expansion(info);
	remove_empty_tokens(&info->tokens_list);
	remove_quotes_from_tokens(info);
	if (info->tokens_list)
		parser(info);
}

static void	process_input_line(char *line, struct s_program_info *info)
{
	if (ft_strlen(line) > 0)
	{
		add_history(line);
		if (!check_unclosed_quotes(line))
		{
			info->exit_status = 2;
			return ;
		}
		handle_tokenization(info, line);
		if (info->command_list && g_sig_status != 130)
			executor(info);
	}
}

static void	init_minishell(struct s_program_info *info, char **envp)
{
	ft_memset(info, 0, sizeof(struct s_program_info));
	info->orig_in = -1;
	info->orig_out = -1;
	get_env_list(&info->env_list, envp, info);
	init_basic_env(info);
}

int	main(int argc, char **argv, char **envp)
{
	char					*line;
	struct s_program_info	info;

	(void)argc;
	(void)argv;
	init_minishell(&info, envp);
	while (1)
	{
		setup_interactive_signals();
		line = readline("ShellWeDance$ ");
		if (g_sig_status)
		{
			info.exit_status = g_sig_status;
			g_sig_status = 0;
		}
		if (!line)
			break ;
		process_input_line(line, &info);
		free(line);
		clean_cycle(&info);
	}
	write(1, "exit\n", 5);
	env_list_destroy(info.env_list);
	rl_clear_history();
	return (0);
}
