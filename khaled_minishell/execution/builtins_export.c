/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:20 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/24 03:46:20 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_key(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	print_export_error(char *arg)
{
	ft_putstr_fd("ShellWeDance: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	print_export_list(struct s_env *env)
{
	char	*eq;

	while (env)
	{
		if (env->content)
		{
			ft_putstr_fd("declare -x ", 1);
			eq = ft_strchr(env->content, '=');
			if (eq)
			{
				write(1, env->content, eq - env->content + 1);
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(eq + 1, 1);
				ft_putendl_fd("\"", 1);
			}
			else
				ft_putendl_fd(env->content, 1);
		}
		env = env->next;
	}
	return (0);
}

static int	process_export_arg(char *arg, struct s_program_info *info)
{
	char	*eq;
	int		status;

	status = 0;
	eq = ft_strchr(arg, '=');
	if (eq)
		*eq = '\0';
	if (is_valid_key(arg))
	{
		if (eq)
			update_env_var(info, arg, eq + 1);
		else if (!find_env_node(info->env_list, arg))
			update_env_var(info, arg, NULL);
	}
	else
	{
		if (eq)
			*eq = '=';
		status = print_export_error(arg);
		eq = NULL;
	}
	if (eq)
		*eq = '=';
	return (status);
}

int	ft_export(char **args, struct s_program_info *info)
{
	int	i;
	int	status;

	if (!args || !info)
		return (0);
	if (!args[1])
		return (print_export_list(info->env_list));
	i = 1;
	status = 0;
	while (args[i])
	{
		if (process_export_arg(args[i], info) != 0)
			status = 1;
		i++;
	}
	return (status);
}
