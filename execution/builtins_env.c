/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:40:10 by halbit            #+#    #+#             */
/*   Updated: 2026/06/14 20:05:39 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_id(char *str)
{
	int	i;

	if (!str || (!ft_isalpha((unsigned char)str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum((unsigned char)str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_entry(char *entry)
{
	char	*eq;

	ft_putstr_fd("declare -x ", 1);
	eq = ft_strchr(entry, '=');
	if (eq)
	{
		write(1, entry, eq - entry);
		write(1, "=\"", 2);
		ft_putstr_fd(eq + 1, 1);
		write(1, "\"", 1);
	}
	else
		ft_putstr_fd(entry, 1);
	write(1, "\n", 1);
}

static int	export_print_sorted(char **env)
{
	int		n;
	char	**sorted;
	int		i;

	n = 0;
	while (env[n])
		n++;
	sorted = malloc(sizeof(char *) * (n + 1));
	if (!sorted)
		return (1);
	i = 0;
	while (i < n)
	{
		sorted[i] = env[i];
		i++;
	}
	sorted[n] = NULL;
	sort_str_arr(sorted, n);
	i = 0;
	while (sorted[i])
		print_export_entry(sorted[i++]);
	free(sorted);
	return (0);
}

int	ft_export(char **args, t_info *info)
{
	int	i;
	int	ret;

	if (!args[1])
		return (export_print_sorted(info->env));
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_id(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		else
			env_update(info, args[i]);
		i++;
	}
	return (ret);
}
