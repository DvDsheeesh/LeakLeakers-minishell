/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 21:01:40 by halbit            #+#    #+#             */
/*   Updated: 2026/06/25 17:59:42 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd, t_info *info)
{
	int	code;
	
	ft_putendl_fd("exit", 1);
	if (!cmd->command_args[1])
		code = info->exit_status;
	else if (!is_numeric(cmd->command_args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->command_args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		code = 2;
	}
	else if (cmd->command_args[1] && cmd->command_args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else
		code = ft_atoi(cmd->command_args[1]) & 255;
	free_vars(info);
	free_cmds(cmd);
	rl_clear_history();
	exit(code);
}
