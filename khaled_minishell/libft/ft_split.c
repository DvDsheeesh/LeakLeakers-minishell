/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:32:42 by kal-haj-          #+#    #+#             */
/*   Updated: 2025/08/13 16:59:29 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_words(const char *str, char deli)
{
	int	num;
	int	in_word;

	num = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != deli && !in_word)
		{
			num++;
			in_word = 1;
		}
		else if (*str == deli)
			in_word = 0;
		str++;
	}
	return (num);
}

static char	*copy_words(const char *str, int len)
{
	char	*copy;
	int		i;

	copy = malloc(len + 1);
	i = 0;
	if (!copy)
		return (NULL);
	while (i < len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static void	free_arr(char **arr, int i)
{
	while (i >= 0)
		free(arr[i--]);
	free(arr);
}

static int	fill_words(char **arr, const char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			arr[i] = copy_words(s, len);
			if (!arr[i])
			{
				free_arr(arr, i);
				return (0);
			}
			i++;
			s += len;
		}
		else
			s++;
	}
	arr[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;

	words = num_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!fill_words(arr, s, c))
		return (NULL);
	return (arr);
}
/*
int	main(void)
{
	char	**arr;

	arr = ft_split("khaled haj", '\0');
	printf("%s", *arr);
}
*/
