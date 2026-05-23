/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:32:03 by melshata          #+#    #+#             */
/*   Updated: 2025/10/08 22:58:35 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

ssize_t	ll(char *s);
// void	ffree(char **s1, char **s2, char **s3);
void	*ffree(char **s1, char **s2, char **s3);
char	*schr(char *s, char c);
char	*my_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

#endif