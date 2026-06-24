/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:29 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 21:48:25 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_sig_status = 130;
	close(STDIN_FILENO);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
