/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:52:22 by halbit            #+#    #+#             */
/*   Updated: 2026/06/22 19:16:50 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**env_copy(char **envp)
{
	int		len;
	int		i;
	char	**copy;

	if (!envp)
		return (NULL);
	len = 0;
	while (envp[len])
		len++;
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			free_arr(copy);
			return (NULL);
		}
		i++;
	}
	copy[len] = NULL;
	return (copy);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_arr(cmds->command_args);
		if (cmds->infile != -1)
			close(cmds->infile);
		if (cmds->outfile != -1)
			close(cmds->outfile);
		free(cmds);
		cmds = tmp;
	}
}

void	sort_str_arr(char **arr, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strncmp(arr[i], arr[j], 4096) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
