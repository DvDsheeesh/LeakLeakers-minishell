/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:53:56 by halbit            #+#    #+#             */
/*   Updated: 2026/06/21 00:15:30 by halbit           ###   ########.fr       */
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

typedef struct s_commands
{
	char				**command_args;
	int					infile;
	int					outfile;
	struct s_commands	*next;
}	t_cmd;

typedef struct s_program_info
{
	char	**env;
	int		exit_status;
}	t_info;

char	*get_path(char *cmd, char **envp);
char	*find_path_in_env(char **envp);
char	*search_in_paths(char **paths, char *cmd);
char	*env_get(char **env, char *key);
int		env_update(t_info *info, char *entry);
int		env_set(t_info *info, char *key, char *val);
void	sort_str_arr(char **arr, int n);
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_info *info);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(char **env);
int		ft_exit(char **args, t_info *info);
int		ft_cd(char **args, t_info *info);
int		ft_export(char **args, t_info *info);
int		ft_unset(char **args, t_info *info);
t_cmd	*parse_line(char *line);
int		execute(t_cmd *cmd, t_info *info);
char	**env_copy(char **envp);
void	free_arr(char **arr);
void	free_cmds(t_cmd *cmds);

#endif
