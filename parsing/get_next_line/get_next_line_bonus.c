/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:00:21 by melshata          #+#    #+#             */
/*   Updated: 2025/09/23 13:10:37 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char *temp)
{
	char	*line;
	ssize_t	i;

	if (schr(temp, '\n'))
		line = malloc(ll(temp) - ll(schr(temp, '\n')) + 2);
	else
		line = malloc(ll(temp) + 1);
	if (!line)
		return (nfree(&temp, NULL, NULL));
	i = 0;
	while (temp[i])
	{
		line[i] = temp[i];
		if (temp[i++] == '\n')
			break ;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_leftover(char *temp)
{
	char	*left;

	if (!schr(temp, '\n') || !temp || !*temp || !ll(schr(temp, '\n') + 1))
		return (NULL);
	left = my_strjoin(NULL, schr(temp, '\n') + 1);
	if (!left)
		return (NULL);
	return (left);
}

static char	*subfun(int fd, char *temp)
{
	ssize_t	rs;
	char	*buff;
	char	*tt;

	rs = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (nfree(&temp, NULL, NULL));
	while (!schr(temp, '\n') && rs != 0)
	{
		rs = read(fd, buff, BUFFER_SIZE);
		if (rs == -1)
			return (nfree(&buff, &temp, NULL));
		buff[rs] = '\0';
		tt = my_strjoin(temp, buff);
		if (!tt)
			return (nfree(&temp, &buff, NULL));
		ffree(&temp, NULL, NULL);
		temp = tt;
	}
	ffree(&buff, NULL, NULL);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	*left[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = my_strjoin(left[fd], NULL);
	if (!temp)
		return (nfree(&left[fd], NULL, NULL));
	temp = subfun(fd, temp);
	if (!temp)
		return (nfree(&left[fd], NULL, NULL));
	line = extract_line(temp);
	if (!line)
		return (nfree(&left[fd], NULL, NULL));
	if (!*line)
		return (nfree(&temp, &line, &left[fd]));
	ffree(&left[fd], NULL, NULL);
	left[fd] = update_leftover(temp);
	ffree(&temp, NULL, NULL);
	return (line);
}
