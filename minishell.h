/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:53:56 by halbit            #+#    #+#             */
/*   Updated: 2026/06/24 22:00:23 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_signal;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_commands
{
	char				**command_args;
	t_redir				*redirs;
	int					infile;
	int					outfile;
	struct s_commands	*next;
}	t_cmd;

typedef struct s_program_info
{
	t_env	*env;
	char	*line;
	char	*word;
	char	*label_arr;
	char	**arg_arr;
	int		exit_status;
}	t_info;

void	free_vars(t_info *vars);
void	free_cmds(t_cmd *cmds);

/* env linked list */
t_env	*env_copy(char **envp);
void	free_env(t_env *env);
char	**env_to_arr(t_env *env);
char	*env_get(t_env *env, char *key);
int		env_update(t_info *info, char *entry);
int		env_set(t_info *info, char *key, char *val);

/* path resolution */
char	*get_path(char *cmd, t_env *env);
char	*find_path_in_env(t_env *env);
char	*search_in_paths(char **paths, char *cmd);

/* redirections + heredoc */
t_redir	*new_redir(t_redir_type type, char *file);
void	free_redirs(t_redir *redirs);
int		open_redirections(t_cmd *cmds, t_info *info);
int		handle_heredoc(char *delim, t_info *info, t_cmd *cmd);

/* builtins */
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_info *info);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_exit(char **args, t_info *info);
int		ft_cd(char **args, t_info *info);
int		ft_export(char **args, t_info *info);
int		ft_unset(char **args, t_info *info);

/* execution */
t_cmd	*parse_line(char *line);
int		execute_pipeline(t_cmd *cmds, t_info *info);
int		execute(t_cmd *cmd, t_info *info);

/* dollar expansion (parse_input.c) */
int		dollar_of_truth(char **line, t_info *vars, int i);

/* utilities */
void	free_arr(char **arr);
void	free_cmds(t_cmd *cmds);
void	sort_str_arr(char **arr, int n);

#endif