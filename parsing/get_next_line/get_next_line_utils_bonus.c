/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:01:09 by melshata          #+#    #+#             */
/*   Updated: 2025/09/23 13:01:30 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	ll(char *s)
{
	ssize_t	l;

	if (!s)
		return (0);
	l = 0;
	while (s[l])
		l++;
	return (l);
}

void	ffree(char **s1, char **s2, char **s3)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	if (s3 && *s3)
	{
		free(*s3);
		*s3 = NULL;
	}
}

void	*nfree(char **s1, char **s2, char **s3)
{
	ffree(s1, s2, s3);
	return (NULL);
}

char	*schr(char *s, char c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

char	*my_strjoin(char *s1, char *s2)
{
	char	*ss;
	ssize_t	i;
	ssize_t	j;

	ss = malloc(ll(s1) + ll(s2) + 1);
	if (!ss)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			ss[i] = s1[i];
			i++;
		}
	}
	j = 0;
	if (s2)
		while (s2[j])
			ss[i++] = s2[j++];
	ss[i] = '\0';
	return (ss);
}
