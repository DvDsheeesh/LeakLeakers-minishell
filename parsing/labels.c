/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 23:47:18 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 16:10:56 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	arg_isoperator(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != '<' && str[i] != '>')
			return (0);
		i++;
	}
	return (1);
}

char	*labelizing(t_info *vars)
{
	char	*label_arr;
	int		i;

	i = 0;
	label_arr = malloc(arr_len(vars->arg_arr) + 1);
	if (!label_arr)
		return (NULL);
	while (vars->arg_arr && vars->arg_arr[i])
	{
		if (ft_strlen(vars->arg_arr[i]) == 1
			&& vars->arg_arr[i][0] == '|')
			label_arr[i] = '3';
		else if (arg_isoperator(vars->arg_arr[i]))
			label_arr[i] = '2';
		else
			label_arr[i] = '1';
		i++;
	}
	label_arr[i] = '\0';
	return (label_arr);
}

int	validate_label(t_info *vars)
{
	int	i;

	i = 0;
	while (vars->label_arr && vars->label_arr[i])
	{
		if (vars->label_arr[i] == '2' || vars->label_arr[i] == '3')
		{
			if (i == (int)(ft_strlen(vars->label_arr) - 1))
				return (wrong_format(vars));
			if (i == 0 && vars->label_arr[i] == '3')
				return (wrong_format(vars));
			if (i > 0 && (vars->label_arr[i - 1] == '2'
					|| vars->label_arr[i - 1] == '3'))
				return (wrong_format(vars));
			if (vars->label_arr[i + 1] == '2'
				|| vars->label_arr[i + 1] == '3')
				return (wrong_format(vars));
		}
		i++;
	}
	return (1);
}
