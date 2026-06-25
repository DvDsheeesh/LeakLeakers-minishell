/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:40:10 by halbit            #+#    #+#             */
/*   Updated: 2026/06/24 10:57:41 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	print_export_entry(char *var, char *value)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(var, 1);
	if (value)
	{
		write(1, "=\"", 2);
		ft_putstr_fd(value, 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

// static int	export_print_sorted(t_env *env)
// {
// 	t_env	*cur;
// 	char	**sorted_vars;
// 	char	**sorted_vals;
// 	int		n;
// 	int		i;
// 	int		j;
// 	char	*tmp_var;
// 	char	*tmp_val;

// 	n = 0;
// 	cur = env;
// 	while (cur)
// 	{
// 		n++;
// 		cur = cur->next;
// 	}
// 	sorted_vars = malloc(sizeof(char *) * (n + 1));
// 	sorted_vals = malloc(sizeof(char *) * (n + 1));
// 	if (!sorted_vars || !sorted_vals)
// 		return (free(sorted_vars), free(sorted_vals), 1);
// 	cur = env;
// 	i = 0;
// 	while (cur)
// 	{
// 		sorted_vars[i] = cur->var;
// 		sorted_vals[i] = cur->value;
// 		cur = cur->next;
// 		i++;
// 	}
// 	sorted_vars[n] = NULL;
// 	sorted_vals[n] = NULL;
// 	i = 0;
// 	while (i < n - 1)
// 	{
// 		j = i + 1;
// 		while (j < n)
// 		{
// 			if (ft_strncmp(sorted_vars[i], sorted_vars[j], 4096) > 0)
// 			{
// 				tmp_var = sorted_vars[i];
// 				sorted_vars[i] = sorted_vars[j];
// 				sorted_vars[j] = tmp_var;
// 				tmp_val = sorted_vals[i];
// 				sorted_vals[i] = sorted_vals[j];
// 				sorted_vals[j] = tmp_val;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < n)
// 	{
// 		print_export_entry(sorted_vars[i], sorted_vals[i]);
// 		i++;
// 	}
// 	free(sorted_vars);
// 	free(sorted_vals);
// 	return (0);
// }

static int	env_count(t_env *env)
{
	int		n;
	t_env	*cur;

	n = 0;
	cur = env;
	while (cur)
	{
		n++;
		cur = cur->next;
	}
	return (n);
}

static char	**collect_env_field(t_env *env, int n, int is_var)
{
	char	**arr;
	t_env	*cur;
	int		i;

	arr = malloc(sizeof(char *) * (n + 1));
	if (!arr)
		return (NULL);
	cur = env;
	i = 0;
	while (cur)
	{
		if (is_var)
			arr[i] = cur->var;
		else
			arr[i] = cur->value;
		cur = cur->next;
		i++;
	}
	arr[n] = NULL;
	return (arr);
}

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
