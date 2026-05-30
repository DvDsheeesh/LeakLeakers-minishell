/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:01:47 by melshata          #+#    #+#             */
/*   Updated: 2025/09/23 13:12:39 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

ssize_t	ll(char *s);
void	ffree(char **s1, char **s2, char **s3);
void	*nfree(char **s1, char **s2, char **s3);
char	*schr(char *s, char c);
char	*my_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

#endif