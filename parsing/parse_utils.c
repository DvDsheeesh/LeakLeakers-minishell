/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 00:07:54 by melshata          #+#    #+#             */
/*   Updated: 2026/06/26 04:36:28 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wrong_format(int *i)
{
	ft_putstr_fd("** invalid syntax **\n", 1);
	*i = -1;
	return (0);
}

int	arr_len(char **arr)
{
	int	l;

	l = 0;
	if (arr)
		while (arr[l])
			l++;
	return (l);
}

char	*ms_extend(char *word, char c)
{
	char	*nw;
	int		i;

	if (word)
		nw = malloc(ft_strlen(word) + 2);
	else
		nw = malloc(2);
	if (!nw)
		return (NULL);
	i = 0;
	while (word && word[i])
	{
		nw[i] = word[i];
		i++;
	}
	free(word);
	nw[i++] = c;
	nw[i] = '\0';
	return (nw);
}
