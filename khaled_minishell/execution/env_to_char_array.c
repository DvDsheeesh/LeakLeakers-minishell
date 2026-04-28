/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_char_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:25 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 21:38:17 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_list_size(struct s_env *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		i++;
		env_list = env_list->next;
	}
	return (i);
}

static void	*free_partial_env(char **env_array, int i)
{
	while (i > 0)
	{
		i--;
		free(env_array[i]);
	}
	free(env_array);
	return (NULL);
}

char	**env_to_char_array(struct s_env *env)
{
	char	**env_array;
	int		i;

	env_array = malloc((env_list_size(env) + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->content)
		{
			env_array[i] = ft_strdup(env->content);
			if (!env_array[i])
				return (free_partial_env(env_array, i));
			i++;
		}
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
