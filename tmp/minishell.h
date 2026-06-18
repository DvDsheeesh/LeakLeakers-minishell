/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:51:00 by melshata          #+#    #+#             */
/*   Updated: 2026/06/18 18:55:43 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft/libft.h"

/*
** t_cmd: represents one full command between pipes
**   args     -> ["ls", "-la", NULL]
**   infile   -> filename after <   (NULL if none)
**   outfile  -> filename after >   (NULL if none)
**   heredoc  -> delimiter after << (NULL if none)
**   append   -> 1 if >>, 0 if >
*/
typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	int				append;
}					t_cmd;

/*
** t_vars: single global state, everything connected
**   env         -> linked list of environment variables
**   cmd_list    -> linked list of t_cmd nodes (one per pipe segment)
**   line        -> raw readline input
**   tokens      -> intermediate 2D array of tokens
**   exit_status -> last command exit status (for $?)
*/
typedef struct s_vars
{
	t_list			*env;
	t_list			*cmd_list;
	char			*line;
	char			**tokens;
	int				exit_status;
}					t_vars;

/* utils.c */
int		ms_strlen(char *s);
int		arr_len(char **arr);
char	*ms_cpy(char *s1);
char	*extend_str(char *word, char c);
void	free_arr(char **arr);
void	free_cmd(void *content);
void	free_vars(t_vars *v);

/* tokenize.c */
char	**tokenize(char *line);

/* cmd_list.c */
t_list	*build_cmd_list(char **tokens);

/* env.c */
t_list	*extract_env(char **env);
char	*get_env_val(t_list *env, char *key);

/* debug.c  (remove before final submission) */
void	print_tokens(char **tokens);
void	print_cmd_list(t_list *cmd_list);

#endif
