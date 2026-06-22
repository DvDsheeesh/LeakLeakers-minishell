/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:07:12 by halbit            #+#    #+#             */
/*   Updated: 2025/08/28 23:13:53 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_2d(char **s2d)
{
	size_t	i;

	i = 0;
	while (s2d[i])
	{
		free(s2d[i]);
		i++;
	}
	free(s2d);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	words;

	if (!s[0])
		return (0);
	words = 0;
	i = 0;
	if (s[i] == c)
		while (s[i] == c)
			i++;
	while (s[i] != 0)
	{
		while (s[i] != 0 && s[i] != c)
			i++;
		words++;
		while (s[i] != 0 && s[i] == c)
			i++;
	}
	return (words);
}

static char	*next_word(char const *s, char c, size_t *a)
{
	size_t	start;
	size_t	i;
	char	*word;

	i = *a;
	while (s[i] != 0 && s[i] == c)
		i++;
	start = i;
	while (s[i] != 0 && s[i] != c)
		i++;
	word = ft_substr (s, start, i - start);
	*a = i;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	a;
	size_t	words;
	char	**s2d;

	if (!s)
		return (NULL);
	i = 0;
	a = 0;
	words = count_words(s, c);
	s2d = (char **)malloc(sizeof (char *) * (words + 1));
	if (!s2d)
		return (NULL);
	while (a < words)
	{
		s2d[a] = next_word(s, c, &i);
		if (!s2d[a])
			return (free_2d(s2d));
		a ++;
	}
	s2d[a] = NULL;
	return (s2d);
}
