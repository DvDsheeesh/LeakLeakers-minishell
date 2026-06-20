/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:58:29 by melshata          #+#    #+#             */
/*   Updated: 2026/06/20 18:34:40 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_status = 0;

void	free_vars(t_info *vars)
{
	if (vars)
	{
		if (vars->env)
			free_arr(vars->env);
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

void	free_cmd(t_cmd *cmd)
{
	if (cmd->command_args)
		free_arr(cmd->command_args);
	free(cmd);
}

void	free_cmd_all(t_cmd *cmd)
{
	if (cmd->next)
		free_cmd_all(cmd->next);
	free_cmd(cmd);
}

void	free_all(t_info *vars, t_cmd *cmd)
{
	if (vars)
		free_vars(vars);
	if (cmd)
		free_cmd_all(cmd);
}

void	to_exit(t_info *vars, t_cmd *cmd)
{
	free_all(vars, cmd);
	exit(0);
}

void	reset_line(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	wrong_format(t_info *vars, int *i)
{
	write(1, "\n", 1);
	ft_putstr_fd("** invalid syntax **\n", 1);
	*i = -1;
}

void	inline_signal(int sig)
{
	(void)sig;
	reset_line();
	g_status = 130;
}

int	len(char *str)
{
	int	l;

	l = 0;
	while (str && str[l])
		l++;
	return (l);
}

int	arr_len(char **arr)
{
	int	l;

	l = 0;
	if (arr)
		while (arr[l])
			l++;
	return (l);
}

t_cmd	*create_command_node(int infile, int outfile)
{
	t_cmd	*aa;

	aa = malloc(sizeof(t_cmd));
	if (!aa)
		return (NULL);
	aa->command_args = NULL;
	aa->infile = infile;
	aa->outfile = outfile;
	aa->next = NULL;
	return (aa);
}

t_cmd	*last_command(t_cmd *lst)
{
	t_cmd	*p;

	if (!lst)
		return (NULL);
	p = lst;
	while (p->next != NULL)
		p = p->next;
	return (p);
}

int	ftpf_putnbr(int n, int i)
{
	if (n == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write (1, "-", 1);
		i++;
		n *= -1;
	}
	if (n > 9)
		i = ftpf_putnbr(n / 10, i);
	n = n % 10 + '0';
	write (1, &n, 1);
	return (i + 1);
}

// void	ft_putstr(char	*str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return ;
// 	while (str && str[i])
// 	{
// 		write(1, &str[i], 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }

char	*ms_cpy(char *s1)
{
	char	*ss;
	int		i;

	ss = malloc(len(s1) + 1);
	if (!ss)
		return (NULL);
	i = 0;
	if (s1 && len(s1) > 0)
		while (s1[i++])
			ss[i - 1] = s1[i - 1];
	if (s1 && len(s1) > 0)
		i--;
	ss[i] = '\0';
	return (ss);
}

char	*extend_arg(char *word, char c)
{
	char	*new_word;
	size_t	i;

	new_word = malloc(len(word) + 2);
	if (!new_word)
		return (NULL);
	i = 0;
	// if (word)
	// {
	// 	while (word[i])
	// 	{
	// 		new_word[i] = word[i];
	// 		i++;
	// 	}
	// }
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

int	join_arg(char **word, char *line, int i, char end_char)
{
	printf("end_char is : %c\n", end_char);
	printf("line[%d] is : %c\n", i, line[i]);
	while (line[i] != end_char)
	{
		if (line[i] == '$')
			NULL;
			// 
		*word = extend_arg(*word, line[i++]);
		printf("i is : %d\n", i);
	}
	printf("line[%d] is : %c\n", i, line[i]);
	return (i);
}

char	**add_arg_to_arr(char **arg_arr, char **word,
	int free_old_arr, int free_word)
{
	int		i;
	char	**new_arr;

	new_arr = malloc(sizeof(char *) * (arr_len(arg_arr) + 2));
	i = 0;
	while (arg_arr && arg_arr[i])
	{
		new_arr[i] = ms_cpy(arg_arr[i]);
		i++;
	}
	if (word && *word)
	{
		new_arr[i++] = ms_cpy(*word);
		if (free_word)
		{
			free(*word);
			*word = NULL;
		}
	}
	new_arr[i] = NULL;
	if (free_old_arr)
		free_arr(arg_arr);
	return (new_arr);
}

char	**special_symbols_parse(char **arg_arr, char *line, int *i)
{
	char	*word;
	char	**new_arr;

	word = NULL;
	word = extend_arg(word, line[*i]);
	if (line[(*i) + 1] == line[*i]
		&& (line[*i] == '<' || line[*i] == '>'))
		word = extend_arg(word, line[(*i)++]);
	new_arr = add_arg_to_arr(arg_arr, &word, 1, 1);
	return (new_arr);
}

// int	dollar_of_truth(char **line, int i, int from_quote) hi man > this is << testing co|de
// {
// 	char	*word;
// 	int		old_i;

// 	old_i = i;
// 	while ((*line)[i] && (isalnum((*line)[i]) || (*line)[i] == '_'))
// 		i++;

// }

char	**split_input_words(char *line, t_info *vars)
{
	int		i;
	char	*word;
	char	**arg_arr;

	i = 0;
	word = NULL;
	arg_arr = NULL;
	while (line && line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = join_arg(&word, line, i + 1, line[i]);
		else if (line[i] == '$' && line[i + 1] != '$')
			NULL;
			// dollar_of_truth
			// add a function that join_arg until not any of [alpha, num, _]
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			if (word)
				arg_arr = add_arg_to_arr(arg_arr, &word, 1, 1);
			arg_arr = special_symbols_parse(arg_arr, line, &i);
		}
		else if (isprint(line[i]) && !isspace(line[i]))
			word = extend_arg(word, line[i]);
		if ((isspace(line[i]) || line[i + 1] == '\0') && word)
			arg_arr = add_arg_to_arr(arg_arr, &word, 1, 1);
		i++;
	}
	return (arg_arr);
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	printf("arr: %p\n", arr);
	// printf("arr[0]: %s", arr[0]);
	while (arr && arr[i])
	{
		// ftpf_putnbr(i, 0);
		ft_putstr_fd(arr[i++], 1);
		write(1, "\n", 1);
	}
}

t_cmd	*extract_env(char **env)
{
	t_cmd	*head;
	int		i;

	head = NULL;
	(void)env;
	// head = create_command_node(env[0]);
	// i = 1;
	// while (i < arr_len(env))
	// 	ft_lstadd_back(&head, create_command_node(env[i]));
	return (head);
}

int	arg_isoperator(char *str)
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

char	*labelizing(t_info *vars)
{
	char	*label_arr;
	int		i;

	i = 0;
	label_arr = malloc(arr_len(vars->arg_arr) + 1);
	while (vars->arg_arr && vars->arg_arr[i])
	{
		if (len(vars->arg_arr[i]) == 1 && vars->arg_arr[i][0] == '|')
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

int	validate_label(t_info *vars)
{
	int	i;

	i = 0;
	while (vars->label_arr && vars->label_arr[i])
	{
		if (vars->label_arr[i] == '2' || vars->label_arr[i] == '3')
		{
			if (i == 0 || i == (len(vars->label_arr) - 1))
				wrong_format(vars, &i);
			else if (vars->label_arr[i - 1] == '2'
				|| vars->label_arr[i - 1] == '3')
				wrong_format(vars, &i);
			else if (vars->label_arr[i + 1] == '2'
				|| vars->label_arr[i + 1] == '3')
				wrong_format(vars, &i);
			if (i == -1)
				return (0);
		}
		i++;
	}
	return (1);
}

// char	**move_word(t_info *vars, t_cmd *list)
// {
// 	char	**temp;

// 	list->content = add_arg_to_arr(list->content, &(vars->arg_arr[0]), 1);
// 	return (list->content);
// }

t_cmd	*parsing_commands(t_info *vars)
{
	t_cmd	*head;
	char	**temp;
	int		i;

	head = create_command_node(0, 0);
	i = 0;
	while (vars->arg_arr && vars->arg_arr[i] && vars->arg_arr[i][0])
	{
		temp = add_arg_to_arr(&(vars->arg_arr[1]), NULL, 0, 0);
		if (len(vars->arg_arr[0]) == 1 && vars->arg_arr[i][0] == '|')
			last_command(head)->next = create_command_node(0, 0);
		else if (arg_isoperator(vars->arg_arr[0]) && vars->arg_arr[0][0] == '<')
			last_command(head)->next = create_command_node(1, 0);
		else if (arg_isoperator(vars->arg_arr[0]) && vars->arg_arr[0][0] == '>')
			last_command(head)->next = create_command_node(0, 1);
		else
			last_command(head)->command_args = add_arg_to_arr(
				last_command(head)->command_args, vars->arg_arr, 1, 0);
		free_arr(vars->arg_arr);
		vars->arg_arr = temp;
	}
	return (head);
}

t_info	*vars_init(char *line, char **env)
{
	t_info	*vars;

	vars = malloc(sizeof(t_info));
	vars->env = add_arg_to_arr(env, NULL, 0, 0);
	vars->arg_arr = NULL;
	vars->label_arr = NULL;
	vars->line = line;
	vars->word = NULL;
	return (vars);
}

void	print_cmd(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		print_arr(cmd->command_args);
		ft_putstr_fd("\n\n", 1);
		cmd = cmd->next;
	}
}
void	set_signals(void)
{
	signal(SIGINT, inline_signal);
	signal(SIGQUIT, SIG_IGN);
}

int	command_process(t_info *vars)
{
	t_cmd	*cmd;

	cmd = parsing_commands(vars);
	g_status = execute(cmd, vars);
	free_cmd_all(cmd);
	return (g_status);
}

int	main(int ac, char **av, char **env)
{
	t_info	*vars;
	char	*line;

	(void)ac;
	(void)av;
	line = NULL;
	while (1)
	{
		set_signals();
		line = readline("\nLeak your thoughts > ");
		if (line == NULL)
			to_exit(NULL, NULL);
		if (line && line[0])
			add_history(line);
		vars = vars_init(line, env);
		vars->arg_arr = split_input_words(line, vars);
		vars->label_arr = labelizing(vars);
		if (validate_label(vars))
		{
			command_process(vars);
		}
		free_vars(vars);
	}
	return (0);
}
