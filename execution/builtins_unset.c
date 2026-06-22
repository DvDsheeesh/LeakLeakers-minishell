/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:05:44 by halbit            #+#    #+#             */
/*   Updated: 2026/06/22 21:55:11 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **args, t_info *info)
{
	t_env	*cur;
	t_env	*prev;
	int		i;

	i = 1;
	while (args[i])
	{
		cur = info->env;
		prev = NULL;
		while (cur)
		{
			if (ft_strncmp(cur->var, args[i], ft_strlen(args[i]) + 1) == 0)
			{
				if (prev)
					prev->next = cur->next;
				else
					info->env = cur->next;
				free(cur->var);
				free(cur->value);
				free(cur);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	return (0);
}
