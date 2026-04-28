/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:18 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/24 03:46:11 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i])
		return (0);
	return (1);
}

static void	exit_numeric_error(char *arg, struct s_program_info *info)
{
	ft_putstr_fd("ShellWeDance: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	destroy_program_info(info);
	exit(255);
}

int	ft_exit(char **args, struct s_program_info *info)
{
	int	status;

	ft_putendl_fd("exit", 2);
	if (args && args[1])
	{
		if (!is_numeric(args[1]))
			exit_numeric_error(args[1], info);
		if (args[2])
		{
			ft_putendl_fd("ShellWeDance: exit: too many arguments", 2);
			return (1);
		}
		status = ft_atoi(args[1]);
		destroy_program_info(info);
		exit(status);
	}
	status = info->exit_status;
	destroy_program_info(info);
	exit(status);
	return (0);
}
