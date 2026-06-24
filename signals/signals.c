/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:15:56 by halbit            #+#    #+#             */
/*   Updated: 2026/06/25 00:28:40 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sigint_handler(int signum)
{
	(void)signum;
	g_signal = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	set_signal(int signum, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sa.sa_flags = flags;
	sigemptyset(&sa.sa_mask);
	sigaction(signum, &sa, NULL);
}

void	setup_interactive_signals(void)
{
	set_signal(SIGINT, sigint_handler, 0);
	set_signal(SIGQUIT, SIG_IGN, 0);
}

void	setup_execution_signals(void)
{
	set_signal(SIGINT, SIG_IGN, 0);
	set_signal(SIGQUIT, SIG_IGN, 0);
}

void	restore_default_signals(void)
{
	set_signal(SIGINT, SIG_DFL, 0);
	set_signal(SIGQUIT, SIG_DFL, 0);
}
