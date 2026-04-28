/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaledhajeid <khaledhajeid@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:25:46 by kal-haj-          #+#    #+#             */
/*   Updated: 2026/02/19 02:42:24 by khaledhajei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

extern int						g_sig_status;

struct							s_env
{
	char						*content;
	struct s_env				*next;
};

enum							e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIR_OUTPUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_INPUT,
	TOKEN_HEREDOC,
	TOKEN_PIPE
};

struct							s_tokens
{
	char						*content;
	enum e_token_type			type;
	struct s_tokens				*previous;
	struct s_tokens				*next;
};

struct							s_replacement_info
{
	char						*original;
	char						*prefix;
	char						*value;
};

struct							s_expander_info
{
	char						*original_str;
	char						*var_name;
	char						*expanded_str;
	int							original_len;
};

enum							e_redirection_type
{
	INFILE,
	OUTFILE_TRUNCATE,
	OUTFILE_APPEND
};

struct							s_redirections_files
{
	char						*name;
	enum e_redirection_type		type;
	struct s_redirections_files	*next;
};

struct							s_commands
{
	char						*absolute_path;
	char						**command_args;
	int							heredoc_fd;
	struct s_redirections_files	*files_list;
	struct s_commands			*next;
};

struct							s_program_info
{
	struct s_expander_info		*expander;
	struct s_replacement_info	*rep;
	struct s_tokens				*tokens_list;
	struct s_env				*env_list;
	struct s_commands			*command_list;
	int							exit_status;
	int							orig_in;
	int							orig_out;
};

struct s_tokens				*tokens_list_new_node(char *value);
void						tokens_list_add_back(struct s_tokens **lst,
								struct s_tokens *new);
void						tokens_list_destroy(struct s_tokens *tokens_list);

struct s_env				*env_list_new_node(char *value);
void						env_list_add_back(struct s_env **lst,
								struct s_env *new);
char						*get_env_var_value(char *var_name,
								struct s_env *env_list);
void						env_list_destroy(struct s_env *env_list);
void						get_env_list(struct s_env **env_list,
								char **envp,
								struct s_program_info *program);

void						initialize_replacement_info(
								struct s_program_info *program,
								char *str, int prefix_len,
								int expand_to_exit_status);
void						initialize_expander_info(
								struct s_program_info *program,
								char *str, int ignore_single_quotes);
void						destroy_expander_info(
								struct s_expander_info *expander);
void						destroy_replacement_info(
								struct s_replacement_info *rep);
void						destroy_program_info(
								struct s_program_info *program);
char						*get_expanded_string(
								struct s_program_info *program,
								char **str, int ignore_single_quotes);
int							expand_quotes(struct s_program_info *program,
								char **str, int *i);
int							expand_to_exit_status(
								struct s_program_info *program,
								char **str, int *i);
char						*replace_var_name_with_value(
								struct s_program_info *program,
								char *str, int *i, int j);

void						*alloc_handling(void *ptr,
								struct s_program_info *program);
int							handle_syserror(int value,
								struct s_program_info *program);

void						files_list_add_back(
								struct s_redirections_files **lst,
								struct s_redirections_files *new);
struct s_redirections_files	*files_list_new_node(char *file_name,
								enum e_redirection_type type);

struct s_commands			*commands_list_new_node(void);
void						commands_list_add_back(struct s_commands **lst,
								struct s_commands *new);
void						command_destroy(struct s_commands *command);
void						commands_list_destroy(
								struct s_commands *commands_list);

void						files_list_destroy(
								struct s_redirections_files *files_list);

void						assign_tokens_types(struct s_tokens **tokens_list);
void						assign_tokens_content(
								struct s_program_info *program,
								char *str);
void						expand_tokens(struct s_program_info *program);
void						split_unquoted_expansion(
								struct s_program_info *program);
void						remove_empty_tokens(struct s_tokens **tokens_list);
char						*remove_quotes_from_token(
								struct s_program_info *program,
								struct s_tokens *token);
void						remove_quotes_from_tokens(
								struct s_program_info *program);
int							check_syntax_errors(
								struct s_tokens *tokens_list,
								struct s_program_info *program);
int							check_unclosed_quotes(char *str);

int							heredoc_is_infile(struct s_tokens *token);
void						handle_heredoc_error(struct s_program_info *program,
								int fd[2], char *line, int fd_stdin);
void						parse_heredoc(struct s_tokens *token,
								struct s_commands *new_command,
								struct s_program_info *program);
void						parser(struct s_program_info *program);

void						free_two_dimensional(char **arr);

void						executor(struct s_program_info *info);
char						**env_to_char_array(struct s_env *env_list);
int							env_list_size(struct s_env *env_list);
char						*get_cmd_path(char *cmd, char **envp);

int							is_builtin(char *cmd);
int							exec_builtin(struct s_commands *cmd,
								struct s_program_info *info);
int							ft_echo(char **args);
int							ft_pwd(void);
int							ft_env(struct s_env *env);
int							ft_exit(char **args,
								struct s_program_info *info);
int							ft_export(char **args,
								struct s_program_info *info);
int							ft_unset(char **args,
								struct s_program_info *info);
int							ft_cd(char **args,
								struct s_program_info *info);
struct s_env				*find_env_node(struct s_env *env, char *key);
void						update_env_var(struct s_program_info *info,
								char *key, char *value);
int							get_env_key_len(char *content);
int							handle_redirections(
								struct s_commands *cmd);
void						handle_cmd_error(char *cmd, char **env_array,
								struct s_program_info *info);
void						handle_child_pipes(struct s_commands *cmd,
								int prev_fd, int pipe_fd[2]);
int							is_valid_key(char *key);
int							create_pipe_and_fork(
								struct s_commands *cmd,
								int pipe_fd[2], pid_t *pid);
void						init_basic_env(struct s_program_info *info);
void						wait_for_executor(pid_t last_pid,
								struct s_program_info *info);

void						setup_interactive_signals(void);
void						setup_execution_signals(void);
void						restore_default_signals(void);
void						rl_replace_line(const char *text,
								int clear_undo);
void						setup_heredoc_signals(void);
void						exec_child_process(struct s_commands *cmd,
								struct s_program_info *info,
								int prev_fd,
								int pipe_fd[2]);
int							ft_strcmp(char *s1, char *s2);
