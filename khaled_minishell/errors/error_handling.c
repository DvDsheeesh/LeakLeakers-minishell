/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:23:06 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/18 20:23:07 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*alloc_handling(void *ptr, struct s_program_info *program)
{
	if (!ptr)
	{
		perror("error");
		destroy_program_info(program);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

int	handle_syserror(int value, struct s_program_info *program)
{
	if (value == -1)
	{
		perror("error");
		destroy_program_info(program);
		exit(EXIT_FAILURE);
	}
	return (value);
}
