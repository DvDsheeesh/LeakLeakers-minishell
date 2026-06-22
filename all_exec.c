
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

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_program_info
{
	// t_env	*env;
	char	**env;
	char	*line;
	char	*word;
	char	*label_arr;
	char	**arg_arr;
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
int		execute_pipeline(t_cmd *cmds, t_info *info);
int		execute(t_cmd *cmd, t_info *info);
char	**env_copy(char **envp);
void	free_arr(char **arr);
void	free_cmds(t_cmd *cmds);

#endif

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0 || ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0 || ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0 || ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (ft_strncmp(cmd, "cd", 3) == 0);
}

int	exec_builtin(t_cmd *cmd, t_info *info)
{
	char	*n;

	n = cmd->command_args[0];
	if (ft_strncmp(n, "echo", 5) == 0)
		return (ft_echo(cmd->command_args));
	if (ft_strncmp(n, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(n, "env", 4) == 0)
		return (ft_env(info->env));
	if (ft_strncmp(n, "exit", 5) == 0)
		return (ft_exit(cmd->command_args, info));
	if (ft_strncmp(n, "export", 7) == 0)
		return (ft_export(cmd->command_args, info));
	if (ft_strncmp(n, "unset", 6) == 0)
		return (ft_unset(cmd->command_args, info));
	return (ft_cd(cmd->command_args, info));
}

static int	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

static char	*cd_get_target(char **args, char **env)
{
	char	*target;

	if (!args[1] || ft_strncmp(args[1], "--", 3) == 0)
	{
		target = env_get(env, "HOME");
		if (!target)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
		return (target);
	}
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		target = env_get(env, "OLDPWD");
		if (!target)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), NULL);
		ft_putendl_fd(target, 1);
		return (target);
	}
	return (args[1]);
}

static void	cd_update_env(t_info *info, char *old)
{
	char	*cwd;

	if (old)
		env_set(info, "OLDPWD", old);
	free(old);
	cwd = getcwd(NULL, 0);
	if (cwd)
		env_set(info, "PWD", cwd);
	free(cwd);
}

int	ft_cd(char **args, t_info *info)
{
	char	*target;
	char	*old;

	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	target = cd_get_target(args, info->env);
	if (!target)
		return (1);
	old = getcwd(NULL, 0);
	if (chdir(target) == -1)
		return (free(old), cd_error(target));
	cd_update_env(info, old);
	return (0);
}

static int	is_valid_id(char *str)
{
	int	i;

	if (!str || (!ft_isalpha((unsigned char)str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum((unsigned char)str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_entry(char *entry)
{
	char	*eq;

	ft_putstr_fd("declare -x ", 1);
	eq = ft_strchr(entry, '=');
	if (eq)
	{
		write(1, entry, eq - entry);
		write(1, "=\"", 2);
		ft_putstr_fd(eq + 1, 1);
		write(1, "\"", 1);
	}
	else
		ft_putstr_fd(entry, 1);
	write(1, "\n", 1);
}

static int	export_print_sorted(char **env)
{
	int		n;
	char	**sorted;
	int		i;

	n = 0;
	while (env[n])
		n++;
	sorted = malloc(sizeof(char *) * (n + 1));
	if (!sorted)
		return (1);
	i = 0;
	while (i < n)
	{
		sorted[i] = env[i];
		i++;
	}
	sorted[n] = NULL;
	sort_str_arr(sorted, n);
	i = 0;
	while (sorted[i])
		print_export_entry(sorted[i++]);
	free(sorted);
	return (0);
}

int	ft_export(char **args, t_info *info)
{
	int	i;
	int	ret;

	if (!args[1])
		return (export_print_sorted(info->env));
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_id(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		else
			env_update(info, args[i]);
		i++;
	}
	return (ret);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_info *info)
{
	int	code;

	ft_putendl_fd("exit", 1);
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (!args[1])
		code = info->exit_status;
	else if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		code = 2;
	}
	else
		code = ft_atoi(args[1]) & 255;
	free_arr(info->env);
	rl_clear_history();
	exit(code);
}

static void	unset_shift(char **env, int j)
{
	while (env[j + 1])
	{
		env[j] = env[j + 1];
		j++;
	}
	env[j] = NULL;
}

int	ft_unset(char **args, t_info *info)
{
	int	i;
	int	j;
	int	klen;

	i = 1;
	while (args[i])
	{
		klen = ft_strlen(args[i]);
		j = 0;
		while (info->env[j])
		{
			if (ft_strncmp(info->env[j], args[i], klen) == 0
				&& (info->env[j][klen] == '=' || info->env[j][klen] == '\0'))
			{
				free(info->env[j]);
				unset_shift(info->env, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || !str[1])
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}

char	*find_path_in_env(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*make_full_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = make_full_path(paths[i], cmd);
		if (!full_path)
			return (free_arr(paths), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_arr(paths), full_path);
		free(full_path);
		i++;
	}
	free_arr(paths);
	return (NULL);
}

static char	*handle_absolute_path(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(cmd));
	path_env = find_path_in_env(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
