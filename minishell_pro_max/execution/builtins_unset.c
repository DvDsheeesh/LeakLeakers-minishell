/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:05:44 by halbit            #+#    #+#             */
/*   Updated: 2026/06/24 11:02:29 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_process(t_info *info, t_env *prev, t_env *cur)
{
	if (prev)
		prev->next = cur->next;
	else
		info->env = cur->next;
	free(cur->var);
	free(cur->value);
	free(cur);
}

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
				unset_process(info, prev, cur);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	return (0);
}
