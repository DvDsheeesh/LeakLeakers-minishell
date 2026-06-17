/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:58:29 by melshata          #+#    #+#             */
/*   Updated: 2026/06/17 20:13:08 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arr_free(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
}

void	free_vars(t_vars *vars)
{
	if (vars->arg_arr)
		arr_free(vars->arg_arr);
	if (vars->label_arr && *(vars->label_arr))
		free(vars->label_arr);
	if (vars->line && *(vars->line))
		free(vars->line);
	if (vars->word)
		free(vars->word);
}

void	to_exit(t_vars *vars)
{
	if (vars)
		free_vars(vars);
	exit(0);
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

void	ft_putstr(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

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

char	**add_arg_to_arr(char **arg_arr, char **word)
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
		new_arr[i++] = ms_cpy(*word);
	new_arr[i] = NULL;
	arr_free(arg_arr);
	free(*word);
	*word = NULL;
	return (new_arr);
}

char	**special_symbols_parse(char **arg_arr, char *line, int *i)
{
	char	*word;
	char	**new_arr;

	word = extend_arg(word, line[*i]);
	if (line[*i + 1] == line[*i] && line[*i] != '|')
		word = extend_arg(word, line[(*i)++]);
	new_arr = add_arg_to_arr(arg_arr, &word);
	free(word);
	// arr_free(arg_arr);
	(*i)++;
	return (new_arr);
}



// int	dollar_of_truth(char **line, int i, int from_quote)
// {
// 	char	*word;
// 	int		old_i;

// 	old_i = i;
// 	while ((*line)[i] && (isalnum((*line)[i]) || (*line)[i] == '_'))
// 		i++;
	
// }

char	**split_input_words(char *line)
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
		else if (line[i] != '$')
			NULL;
			// dollar_of_truth
			// add a function that join_arg until not any of [alpha, num, _]
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			if (word)
				arg_arr = add_arg_to_arr(arg_arr, &word);
			// TODO: fix this function
			// arg_arr = special_symbols_parse(arg_arr, line, &i);
			word = extend_arg(word, line[i]);
			if (line[i + 1] == line[i]
				&& (line[i] == '<' || line[i] == '>'))
				word = extend_arg(word, line[i++]);
			arg_arr = add_arg_to_arr(arg_arr, &word);
		}
		else if (isprint(line[i]) && !isspace(line[i]))
			word = extend_arg(word, line[i]);
		if ((isspace(line[i]) || line[i + 1] == '\0') && word)
			arg_arr = add_arg_to_arr(arg_arr, &word);
		i++;
	}
	return (arg_arr);
}

void	arr_print(char **arr)
{
	int	i;

	i = 0;
	printf("arr: %p\n", arr);
	// printf("arr[0]: %s", arr[0]);
	while (arr && arr[i])
	{
		// ftpf_putnbr(i, 0);
		ft_putstr(arr[i++]);
	}
}

t_list	*extract_env(char **env)
{
	t_list	*head;
	int		i;

	head = NULL;
	(void)env;
	// head = ft_lstnew(env[0]);
	// i = 1;
	// while (i < arr_len(env))
	// 	ft_lstadd_back(&head, ft_lstnew(env[i]));
	return (head);
}

int	arg_isoperator(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != '<' || str[i] != '>')
			return (0);
	}
	return (1);
}

char	*labelizing(t_vars *vars)
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

void	validate_label(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->label_arr && vars->label_arr[i])
	{
		if (vars->label_arr[i] == '2' || vars->label_arr[i] == '3')
		{
			(void)i;
			if (i != 0 && (vars->label_arr[i - 1] == '2'
					|| vars->label_arr[i - 1] == '3'))
				to_exit(vars);
			if (i < (len(vars->label_arr) - 1) && (vars->label_arr[i + 1] == '2'
					|| vars->label_arr[i + 1] == '3'))
				to_exit(vars);
		}
		i++;
	}
}

char	**move_word(t_vars *vars, t_list *list)
{
	char	**temp;

	list->content = add_arg_to_arr(list->content, &(vars->arg_arr[0]));
	temp = add_arg_to_arr(&(vars->arg_arr[1]), NULL);
	arr_free(vars->arg_arr);
	vars->arg_arr = temp;
	return (list->content);
}

t_list	*parsing_commands(t_vars *vars)
{
	t_list	*head;
	int		i;
	int		is_input;
	int		is_output;

	is_input = 0;
	is_output = 0;
	head = ft_lstnew(NULL);
	i = 0;
	while(vars->arg_arr && vars->arg_arr[i] && vars->arg_arr[i][0])
	{
		if (len(vars->arg_arr[0]) == 1 && vars->arg_arr[i][0] == '|')
			ft_lstlast(head)->next = ft_lstnew(NULL);
		else if (arg_isoperator(vars->arg_arr[0]) && vars->arg_arr[0][0] == '<')
		{
			is_input = 1;
			is_output = 0;
		}
		else if (arg_isoperator(vars->arg_arr[0]) && vars->arg_arr[0][0] == '<')
		{
			is_input = 0;
			is_output = 1;
		}
		else
			vars->arg_arr = move_word(vars, ft_lstlast(head));
	}
	return (head);
}

t_vars	*vars_init(char *line)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	vars->arg_arr = NULL;
	vars->label_arr = NULL;
	vars->line = line;
	vars->word = NULL;
	return (vars);
}

void	inline_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// g_sig_status = 130;
}

int	main(int ac, char **av, char **env)
{
	t_vars	*vars;
	char	*line;

	(void)ac;
	(void)av;
	line = NULL;
	vars = NULL;
	while (1)
	{
		printf("\ntest1\n");
		signal(SIGINT, inline_signal);
		signal(SIGQUIT, SIG_IGN);
		printf("\ntest2\n");
		line = readline("\nLeak your thoughts > ");
		printf("\ntest3\n");
		// if (line == NULL)
		// 	to_exit(vars);
		printf("\ntest4\n");
		if (line[0])
			add_history(line);
		printf("\ntest5\n");
		vars = vars_init(line);
		printf("\ntest6\n");
		vars->arg_arr = split_input_words(line);
		if (vars->arg_arr)
			arr_print(vars->arg_arr);
		// printf("\ntest6.1\n");
		// TODO: add a function that assign labels to words
		vars->label_arr = labelizing(vars);
		// printf("\ntest6.2\n");
		// TODO: add a validation function based on the labels
		validate_label(vars);
		// TODO: add a parsing function that split each command in a node in a linked list

		// ft_putstr(line);
		printf("\ntest7\n");
		if (vars)
			free_vars(vars);
	}
	return (0);
}
