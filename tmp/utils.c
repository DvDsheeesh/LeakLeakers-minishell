/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:51:00 by melshata          #+#    #+#             */
/*   Updated: 2026/06/18 18:55:43 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns length of string (NULL-safe) */
int	ms_strlen(char *s)
{
	int	l;

	l = 0;
	while (s && s[l])
		l++;
	return (l);
}

/* Returns number of elements in a NULL-terminated array */
int	arr_len(char **arr)
{
	int	l;

	l = 0;
	while (arr && arr[l])
		l++;
	return (l);
}

/* Duplicates a string (NULL-safe, returns "" for NULL input) */
char	*ms_cpy(char *s1)
{
	char	*ss;
	int		i;

	if (!s1)
		return (ft_strdup(""));
	ss = malloc(ms_strlen(s1) + 1);
	if (!ss)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ss[i] = s1[i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}

/*
** Appends one character to a heap string.
** Frees the old string, returns the new one.
** Safe to call with word == NULL (starts a new string).
*/
char	*extend_str(char *word, char c)
{
	char	*new_word;
	int		i;

	new_word = malloc(ms_strlen(word) + 2);
	if (!new_word)
		return (NULL);
	i = 0;
	while (word && word[i])
	{
		new_word[i] = word[i];
		i++;
	}
	free(word);
	new_word[i++] = c;
	new_word[i] = '\0';
	return (new_word);
}

/* Frees a NULL-terminated 2D array */
void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

/* Destructor for a t_cmd node (used with ft_lstclear) */
void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (!cmd)
		return ;
	free_arr(cmd->args);
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd->heredoc);
	free(cmd);
}

/* Frees all heap memory inside t_vars */
void	free_vars(t_vars *v)
{
	ft_lstclear(&v->cmd_list, free_cmd);
	free_arr(v->tokens);
	free(v->line);
	v->tokens = NULL;
	v->line = NULL;
	v->cmd_list = NULL;
}
