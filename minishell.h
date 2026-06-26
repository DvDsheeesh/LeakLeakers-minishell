/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:53:56 by halbit            #+#    #+#             */
/*   Updated: 2026/06/26 10:56:26 by melshata         ###   ########.fr       */
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

/* signal setup */
void	setup_inline_signals(void);
void	setup_execution_signals(void);
void	default_signals(void);
void	set_heredoc_sig(void);

void	free_vars(t_info *vars);
t_info	*vars_init(char *line, char **env);
void	reset_vars(t_info *vars);

/* parsing utils */
char	**add_arg_to_arr(char **arr, char **word,
			int free_old, int free_word);
char	*ms_extend(char *word, char c);
int		wrong_format(int *i);
int		arr_len(char **arr);
int		join_arg(char **word, char *line, int i, char end_char);
int		join_arg_dq(char **word, char **line, t_info *vars, int i);
char	**split_input_words(char *line, t_info *vars);
char	*labelizing(t_info *vars);
int		validate_label(t_info *vars);
int		command_process(t_info *vars);

/* env additional utils */
int		is_valid_id(char *str);
void	print_export_entry(char *var, char *value);
int		env_count(t_env *env);
char	**collect_env_field(t_env *env, int n, int is_var);

/* env linked list */
t_env	*extract_env(char **env);
void	free_env(t_env *env);
char	**env_to_arr(t_env *env);
char	*env_get(t_env *env, char *key);
int		env_update(t_info *info, char *entry);
int		env_set(t_info *info, char *key, char *val);

/* path resolution */
char	*get_path(char *cmd, t_env *env);

/* redirections + heredoc */
t_redir	*new_redir(t_redir_type type, char *file);
int		open_redirections(t_cmd *cmds, t_info *info);
int		handle_heredoc(char *delim, t_info *info, t_cmd *cmd);

t_cmd	*last_command(t_cmd *lst);
t_cmd	*create_command_node(void);

/* builtins */
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_info *info);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_exit(t_cmd *cmd, t_info *info);
int		ft_cd(char **args, t_info *info);
int		ft_export(char **args, t_info *info);
int		ft_unset(char **args, t_info *info);

/* execution */
int		execute_pipeline(t_cmd *cmds, t_info *info);
int		execute(t_cmd *cmd, t_info *info);
int		exit_child(int status);

/* dollar expansion (parse_input.c) */
int		dollar_of_truth(char **line, t_info *vars, int i);

/* utilities */
void	free_arr(char **arr);
void	free_cmds(t_cmd *cmds);

#endif