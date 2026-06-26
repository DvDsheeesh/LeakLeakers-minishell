/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 01:17:51 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 02:17:49 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_id(char *str)
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

void	print_export_entry(char *var, char *value)
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

int	env_count(t_env *env)
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

char	**collect_env_field(t_env *env, int n, int is_var)
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
