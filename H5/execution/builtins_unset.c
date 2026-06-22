/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:05:44 by halbit            #+#    #+#             */
/*   Updated: 2026/06/21 00:15:05 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_shift(char **env, int j)
{
	while (env[j + 1])
	{
		env[j] = env[j + 1];
		j++;
	}
	env[j] = NULL;
}

int	ft_unset(char **args, t_info *info)
{
	int	i;
	int	j;
	int	klen;

	i = 1;
	while (args[i])
	{
		klen = ft_strlen(args[i]);
		j = 0;
		while (info->env[j])
		{
			if (ft_strncmp(info->env[j], args[i], klen) == 0
				&& (info->env[j][klen] == '=' || info->env[j][klen] == '\0'))
			{
				free(info->env[j]);
				unset_shift(info->env, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
