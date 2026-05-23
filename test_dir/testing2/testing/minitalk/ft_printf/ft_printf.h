/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:44:05 by melshata          #+#    #+#             */
/*   Updated: 2025/09/11 11:36:10 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ftpf_putnbr(int n, int i);
int	ftpf_puthex(int n, int i, char c);
int	ftpf_putuns(unsigned int u, int i);
int	ftpf_putchr(int c);
int	ftpf_putstr(char *s);
int	ftpf_putptr(void *p, int i);
int	ft_printf(const char *sss, ...);

#endif