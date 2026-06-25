/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:58:29 by melshata          #+#    #+#             */
/*   Updated: 2026/06/25 22:26:44 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

/* ── free helpers ─────────────────────────────────────────────────────────── */

void	free_vars(t_info *vars)
{
	if (vars)
	{
		if (vars->env)
			free_env(vars->env);
		vars->env = NULL;
		if (vars->arg_arr)
			free_arr(vars->arg_arr);
		vars->arg_arr = NULL;
		if (vars->label_arr)
			free(vars->label_arr);
		vars->label_arr = NULL;
		if (vars->line)
			free(vars->line);
		vars->line = NULL;
		if (vars->word)
			free(vars->word);
		vars->word = NULL;
		free(vars);
	}
}

/* ── signal ───────────────────────────────────────────────────────────────── */

// void	reset_line(void)
// {
// 	write(1, "\n", 2);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	inline_signal(int sig)
// {
// 	(void)sig;
// 	reset_line();
// 	g_signal = 130;
// }

// void	set_signals(void)
// {
// 	signal(SIGINT, inline_signal);
// 	signal(SIGQUIT, SIG_IGN);
// }

/* ── string helpers ───────────────────────────────────────────────────────── */

int	wrong_format(int *i)
{
	// write(1, "\n", 1);
	ft_putstr_fd("** invalid syntax **\n", 1);
	*i = -1;
	return (0);
}

static int	arr_len(char **arr)
{
	int	l;

	l = 0;
	if (arr)
		while (arr[l])
			l++;
	return (l);
}

static char	*ms_extend(char *word, char c)
{
	char	*nw;
	int		i;

	nw = malloc((word ? ft_strlen(word) : 0) + 2);
	if (!nw)
		return (NULL);
	i = 0;
	while (word && word[i])
	{
		nw[i] = word[i];
		i++;
	}
	free(word);
	nw[i++] = c;
	nw[i] = '\0';
	return (nw);
}

/* ── arg array helpers ────────────────────────────────────────────────────── */

static char	**add_arg_to_arr(char **arr, char **word,
	int free_old, int free_word)
{
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * (arr_len(arr) + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (arr && arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	if (word && *word)
	{
		new[i++] = ft_strdup(*word);
		if (free_word)
		{
			free(*word);
			*word = NULL;
		}
	}
	new[i] = NULL;
	if (free_old)
		free_arr(arr);
	return (new);
}

/* ── quoted / joined arg ──────────────────────────────────────────────────── */

static int	join_arg(char **word, char *line, int i, char end_char)
{
	while (line[i] && line[i] != end_char)
	{
		*word = ms_extend(*word, line[i]);
		i++;
	}
	return (i);
}

static int	join_arg_dq(char **word, char **line, t_info *vars, int i)
{
	while ((*line)[i] && (*line)[i] != '"')
	{
		if ((*line)[i] == '$' && (*line)[i + 1] != '$'
			&& (ft_isalnum((unsigned char)(*line)[i + 1])
				|| (*line)[i + 1] == '_' || (*line)[i + 1] == '?'))
			i = dollar_of_truth(line, vars, i);
		else
		{
			*word = ms_extend(*word, (*line)[i]);
			i++;
		}
	}
	return (i);
}

/* ── operator tokenizer ───────────────────────────────────────────────────── */

static char	**special_symbols_parse(char **arg_arr, char *line,
	char **word, int *i)
{
	char	**new_arr;

	if (*word)
		arg_arr = add_arg_to_arr(arg_arr, word, 1, 1);
	*word = ms_extend(*word, line[*i]);
	if (line[(*i) + 1] == line[*i]
		&& (line[*i] == '<' || line[*i] == '>'))
		*word = ms_extend(*word, line[(*i)++]);
	new_arr = add_arg_to_arr(arg_arr, word, 1, 1);
	return (new_arr);
}

/* ── env linked list ──────────────────────────────────────────────────────── */

t_env	*env_new(char *element)
{
	t_env	*node;
	char	*eq;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	eq = ft_strchr(element, '=');
	if (eq)
	{
		node->var = ft_substr(element, 0, eq - element);
		node->value = ft_strdup(eq + 1);
	}
	else
	{
		node->var = ft_strdup(element);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

t_env	*extract_env(char **env)
{
	t_env	*head;
	t_env	*cur;
	t_env	*node;
	int		i;

	if (!env || !env[0])
		return (NULL);
	head = NULL;
	cur = NULL;
	i = 0;
	while (env[i])
	{
		node = env_new(env[i]);
		if (!node)
			return (head);
		if (!head)
			head = node;
		else
			cur->next = node;
		cur = node;
		i++;
	}
	return (head);
}

/* ── dollar expansion ─────────────────────────────────────────────────────── */

static char	*replace_range(char *line, int start, int end, char *new_word)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = malloc(ft_strlen(line) + ft_strlen(new_word)
			- (end - start) + 1);
	if (!new_line)
		return (line);
	i = 0;
	while (i < start && line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	j = 0;
	while (new_word[j])
		new_line[i++] = new_word[j++];
	j = end;
	while (line[j])
		new_line[i++] = line[j++];
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

int	dollar_exit(char **line, int start, t_info *vars)
{
	char	*code;

	code = ft_itoa(vars->exit_status);
	if (!code)
		return (start + 2);
	*line = replace_range(*line, start, start + 2, code);
	free(code);
	return (start);
}

int	dollar_of_truth(char **line, t_info *vars, int i)
{
	int		start;
	int		end;
	char	*var_name;
	char	*value;

	start = i++;
	if ((*line)[i] == '?')
		return (dollar_exit(line, start, vars));
	while ((*line)[i]
		&& (ft_isalnum((*line)[i]) || (*line)[i] == '_'))
		i++;
	end = i;
	if (end == start + 1)
		return (end);
	var_name = ft_substr(*line, start + 1, end - start - 1);
	if (!var_name)
		return (end);
	value = env_get(vars->env, var_name);
	free(var_name);
	if (!value)
		value = "";
	*line = replace_range(*line, start, end, value);
	return (start);
}

/* ── tokenizer ────────────────────────────────────────────────────────────── */

int	is_var_name(char c, char *mline, int i)
{
	return (ft_isalnum(mline[i + 1]) || mline[i + 1] == '_'
		|| mline[i + 1] == '?');
}

char	**split_input_words(char *line, t_info *vars)
{
	char	*mline;
	int		i;
	char	**arg_arr;

	mline = ft_strdup(line);
	if (!mline)
		return (NULL);
	i = 0;
	arg_arr = NULL;
	while (mline && mline[i])
	{
		if (mline[i] == '\'')
			i = join_arg(&(vars->word), mline, i + 1, '\'');
		else if (mline[i] == '"')
			i = join_arg_dq(&(vars->word), &mline, vars, i + 1);
		else if (mline[i] == '$' && mline[i + 1] != '$'
			&& is_var_name(mline[i + 1], mline, i))
		{
			i = dollar_of_truth(&mline, vars, i);
			continue ;
		}
		else if (mline[i] == '<' || mline[i] == '>' || mline[i] == '|')
			arg_arr = special_symbols_parse(arg_arr, mline, &(vars->word), &i);
		else if (ft_isprint(mline[i]) && mline[i] != ' ' && mline[i] != '\t')
			vars->word = ms_extend(vars->word, mline[i]);
		if ((mline[i] == ' ' || mline[i] == '\t' || mline[i + 1] == '\0')
			&& vars->word)
			arg_arr = add_arg_to_arr(arg_arr, &(vars->word), 1, 1);
		i++;
	}
	free(mline);
	return (arg_arr);
}

/* ── labeling / validation ────────────────────────────────────────────────── */

static int	arg_isoperator(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != '<' && str[i] != '>')
			return (0);
		i++;
	}
	return (1);
}

static char	*labelizing(t_info *vars)
{
	char	*label_arr;
	int		i;

	i = 0;
	label_arr = malloc(arr_len(vars->arg_arr) + 1);
	if (!label_arr)
		return (NULL);
	while (vars->arg_arr && vars->arg_arr[i])
	{
		if (ft_strlen(vars->arg_arr[i]) == 1
			&& vars->arg_arr[i][0] == '|')
			label_arr[i] = '3';
		else if (arg_isoperator(vars->arg_arr[i]))
			label_arr[i] = '2';
		else
			label_arr[i] = '1';
		i++;
	}
	label_arr[i] = '\0';
	return (label_arr);
}

static int	validate_label(t_info *vars)
{
	int	i;

	i = 0;
	while (vars->label_arr && vars->label_arr[i])
	{
		if (vars->label_arr[i] == '2' || vars->label_arr[i] == '3')
		{
			if (i == (int)(ft_strlen(vars->label_arr) - 1))
				return (wrong_format(&i));
			if (i == 0 && vars->label_arr[i] == '3')
				return (wrong_format(&i));
			if (i > 0 && (vars->label_arr[i - 1] == '2'
					|| vars->label_arr[i - 1] == '3'))
				return (wrong_format(&i));
			if (vars->label_arr[i + 1] == '2'
				|| vars->label_arr[i + 1] == '3')
				return (wrong_format(&i));
		}
		i++;
	}
	return (1);
}

/* ── command building ─────────────────────────────────────────────────────── */

static t_cmd	*last_command(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static t_cmd	*create_command_node(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->command_args = NULL;
	node->redirs = NULL;
	node->infile = -1;
	node->outfile = -1;
	node->next = NULL;
	return (node);
}

t_redir	*new_redir(t_redir_type type, char *file)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->file = ft_strdup(file);
	r->next = NULL;
	return (r);
}

static void	append_redir(t_redir **head, t_redir *r)
{
	t_redir	*cur;

	if (!r)
		return ;
	if (!*head)
	{
		*head = r;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = r;
}

int	command_looping(char **arr, t_cmd *last, int i)
{
	if (ft_strncmp(arr[i], "|", 2) == 0)
		last->next = create_command_node();
	else if (ft_strncmp(arr[i], "<<", 3) == 0 && arr[i + 1])
		append_redir(&last->redirs, new_redir(REDIR_HEREDOC, arr[++i]));
	else if (ft_strncmp(arr[i], "<", 2) == 0 && arr[i + 1])
		append_redir(&last->redirs, new_redir(REDIR_IN, arr[++i]));
	else if (ft_strncmp(arr[i], ">>", 3) == 0 && arr[i + 1])
		append_redir(&last->redirs, new_redir(REDIR_APPEND, arr[++i]));
	else if (ft_strncmp(arr[i], ">", 2) == 0 && arr[i + 1])
		append_redir(&last->redirs, new_redir(REDIR_OUT, arr[++i]));
	else
		last->command_args = add_arg_to_arr(
				last->command_args, &arr[i], 1, 0);
	return (i);
}

static t_cmd	*parsing_commands(t_info *vars)
{
	t_cmd		*head;
	t_cmd		*last;
	char		**arr;
	int			i;

	head = create_command_node();
	arr = vars->arg_arr;
	i = 0;
	while (arr && arr[i])
	{
		last = last_command(head);
		i = command_looping(arr, last, i);
		// if (ft_strncmp(arr[i], "|", 2) == 0)
		// 	last->next = create_command_node();
		// else if (ft_strncmp(arr[i], "<<", 3) == 0 && arr[i + 1])
		// 	append_redir(&last->redirs, new_redir(REDIR_HEREDOC, arr[++i]));
		// else if (ft_strncmp(arr[i], "<", 2) == 0 && arr[i + 1])
		// 	append_redir(&last->redirs, new_redir(REDIR_IN, arr[++i]));
		// else if (ft_strncmp(arr[i], ">>", 3) == 0 && arr[i + 1])
		// 	append_redir(&last->redirs, new_redir(REDIR_APPEND, arr[++i]));
		// else if (ft_strncmp(arr[i], ">", 2) == 0 && arr[i + 1])
		// 	append_redir(&last->redirs, new_redir(REDIR_OUT, arr[++i]));
		// else
		// 	last->command_args = add_arg_to_arr(
		// 			last->command_args, &arr[i], 1, 0);
		i++;
	}
	return (head);
}

/* ── info init ────────────────────────────────────────────────────────────── */

static t_info	*vars_init(char *line, char **env)
{
	t_info	*vars;

	vars = malloc(sizeof(t_info));
	if (!vars)
		return (NULL);
	vars->env = extract_env(env);
	vars->arg_arr = NULL;
	vars->label_arr = NULL;
	vars->line = line;
	vars->word = NULL;
	vars->exit_status = 0;
	return (vars);
}

/* ── command process (parse + execute) ────────────────────────────────────── */

static int	command_process(t_info *vars)
{
	t_cmd	*cmd;

	cmd = parsing_commands(vars);
	if (open_redirections(cmd, vars))
	{
		free_cmds(cmd);
		return (1);
	}
	setup_execution_signals();
	vars->exit_status = execute(cmd, vars);
	free_cmds(cmd);
	setup_inline_signals();
	return (vars->exit_status);
}

/* ── main ─────────────────────────────────────────────────────────────────── */

static void	reset_vars(t_info *vars)
{
	free_arr(vars->arg_arr);
	vars->arg_arr = NULL;
	free(vars->label_arr);
	vars->label_arr = NULL;
	free(vars->word);
	vars->word = NULL;
	free(vars->line);
	vars->line = NULL;
}

void	main_loop(char **line, t_info *vars)
{
	// set_signals();
	setup_inline_signals();
	*line = readline("minishell$");
	if (g_signal)
	{
		vars->exit_status = g_signal;
		g_signal = 0;
	}
	if (*line == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free_vars(vars);
		exit(0);
	}
	if (*line && (*line)[0])
		add_history(*line);
	reset_vars(vars);
	vars->line = *line;
	vars->arg_arr = split_input_words(*line, vars);
	vars->label_arr = labelizing(vars);
	if (validate_label(vars))
		command_process(vars);
}

int	main(int ac, char **av, char **env)
{
	t_info	*vars;
	char	*line;

	(void)ac;
	(void)av;
	g_signal = 0;
	vars = vars_init(NULL, env);
	if (!vars)
		return (1);
	while (1)
	{
		main_loop(&line, vars);
	}
	return (0);
}
