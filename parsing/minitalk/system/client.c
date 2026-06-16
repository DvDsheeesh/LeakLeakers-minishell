/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:04:28 by melshata          #+#    #+#             */
/*   Updated: 2026/01/21 13:47:10 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int	g_var;

void	exit_fun(const char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		write (2, &msg[i++], 1);
	exit (1);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		num = num * 10 + (nptr[i++] - '0');
	if (nptr[i])
		exit_fun ("Error\nwrong input format\n");
	return ((int)(num));
}

void	ack_receiver(int sig)
{
	(void)sig;
	g_var = 1;
}

void	str_sender(char *c, int s_pid)
{
	int	i;

	if (kill(s_pid, 0) == -1)
		exit_fun ("Error\ncan't access pid\n");
	while (*c || *(c - 1))
	{
		i = 8;
		while (i > 0)
		{
			g_var = 0;
			if (((*c) >> --i) % 2 == 1)
				kill (s_pid, SIGUSR2);
			else
				kill (s_pid, SIGUSR1);
			while (!g_var)
				;
		}
		if (!(*c))
			break ;
		c++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
		exit_fun ("Error\nmust take -server_pid- -message-\n");
	signal (SIGUSR1, ack_receiver);
	str_sender (av[2], ft_atoi (av[1]));
	return (0);
}
