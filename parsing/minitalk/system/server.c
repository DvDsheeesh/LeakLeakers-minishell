/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:39:56 by melshata          #+#    #+#             */
/*   Updated: 2026/01/21 13:46:13 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdlib.h>

#include "../ft_printf/ft_printf.h"

size_t	len(char *s)
{
	size_t	l;

	if (!s)
		return (0);
	l = 0;
	while (s[l])
		l++;
	return (l);
}

static char	*extend_str(char *s1, char c)
{
	char	*ss;
	size_t	i;

	ss = malloc(len(s1) + 2);
	if (!ss)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			ss[i] = s1[i];
			i++;
		}
	}
	free(s1);
	ss[i++] = c;
	ss[i] = '\0';
	return (ss);
}

void	singal_handler(int sig, siginfo_t *info, void *context)
{
	static int	bitcount = 0;
	static char	chrr = 0;
	static char	*msg = NULL;
	char		bit;

	(void) context;
	bit = 0;
	if (sig == SIGUSR2)
		bit = 1;
	bitcount++;
	chrr = (chrr << 1) + bit;
	if (bitcount == 8)
	{
		msg = extend_str (msg, chrr);
		if (chrr == 0)
		{
			ft_printf ("%s\n", msg);
			free (msg);
			msg = NULL;
		}
		bitcount = 0;
		chrr = 0;
	}
	kill (info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = singal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf ("pid: %d\n", getpid());
	while (1)
		;
}
