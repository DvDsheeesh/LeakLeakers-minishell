/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:40:10 by halbit            #+#    #+#             */
/*   Updated: 2026/06/26 09:24:00 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	swap_entries(char **vars, char **vals, int i, int j)
{
	char	*tmp;

	tmp = vars[i];
	vars[i] = vars[j];
	vars[j] = tmp;
	tmp = vals[i];
	vals[i] = vals[j];
	vals[j] = tmp;
}

static void	sort_env_entries(char **vars, char **vals, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strncmp(vars[i], vars[j], 4096) > 0)
				swap_entries(vars, vals, i, j);
			j++;
		}
		i++;
	}
}

static int	export_print_sorted(t_env *env)
{
	char	**sorted_vars;
	char	**sorted_vals;
	int		n;
	int		i;

	n = env_count(env);
	sorted_vars = collect_env_field(env, n, 1);
	sorted_vals = collect_env_field(env, n, 0);
	if (!sorted_vars || !sorted_vals)
		return (free(sorted_vars), free(sorted_vals), 1);
	sort_env_entries(sorted_vars, sorted_vals, n);
	i = 0;
	while (i < n)
	{
		print_export_entry(sorted_vars[i], sorted_vals[i]);
		i++;
	}
	free(sorted_vars);
	free(sorted_vals);
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
