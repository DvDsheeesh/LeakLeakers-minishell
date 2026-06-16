#include "minishell.h"

void	arr_free(char **arg_arr)
{
	int	i;

	i = 0;
	while (arg_arr && arg_arr[i])
		free(arg_arr[i++]);
	free(arg_arr);
}

int len(char *str)
{
	int	l;

	l = 0;
	while(str && str[l])
		l++;
	return (l);
}

int	arr_len(char **arr)
{
	int	l;

	l = 0;
	if (arr)
		while(arr[l])
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

void ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while(str && str[i])
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
		{*word = extend_arg(*word, line[i++]);
		printf("i is : %d\n", i);}
	printf("line[%d] is : %c\n", i, line[i]);
	return (i);
}

char	**add_arg_to_arr(char **arg_arr, char **word)
{
	int		i;
	int		l;
	char	**new_arr;

	l = arr_len(arg_arr) + 2;
	new_arr = malloc(sizeof(char *) * l);
	i = 0;
	while (arg_arr && arg_arr[i])
	{
		new_arr[i] = ms_cpy(arg_arr[i]);
		i++;
	}
	new_arr[i] = ms_cpy(*word);
	new_arr[++i] = NULL;
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

char	**split_input_words(char *line)
{
	int	i;
	char	*word;
	char	**arg_arr;

	i = 0;
	word = NULL;
	arg_arr = NULL;
	while (line && line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = join_arg(&word, line, i + 1, line[i]);
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			if (word)
				arg_arr = add_arg_to_arr(arg_arr, &word);
			// TODO: fix this function
			// arg_arr = special_symbols_parse(arg_arr, line, &i);
			word = extend_arg(word, line[i]);
			if (line[i + 1] == line[i] && line[i] != '|')
				word = extend_arg(word, line[i++]);
			arg_arr = add_arg_to_arr(arg_arr, &word);
		}
		else if (isprint(line[i]) && !isspace(line[i]))
			word = extend_arg(word, line[i]);
		if ((isspace(line[i]) || line[i + 1] == '\0') && word)
		{arg_arr = add_arg_to_arr(arg_arr, &word);printf("is_space, new word: %s\n", arg_arr[arr_len(arg_arr) - 1]);}
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

// t_list	*extract_env(char **env)
// {
// 	t_list	*head;
// 	int		i;

// 	head = NULL;
// 	(void)env;
// 	// head = ft_lstnew(env[0]);
// 	// i = 1;
// 	// while (i < arr_len(env))
// 	// 	ft_lstadd_back(&head, ft_lstnew(env[i]));
// 	return (head);
// }

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

int	*labelizing(t_vars vars)
{
	int	*label_arr;
	int	i;

	i = 0;
	label_arr = malloc(arr_len(vars.arg_arr) * sizeof(int));
	while (vars.arg_arr && vars.arg_arr[i])
	{
		if (len(vars.arg_arr[i]) == 1 && vars.arg_arr[i] == '|')
			label_arr[i] = 3;
		else if (arg_isoperator(vars.arg_arr[i]))
			label_arr[i] = 2;
		else
			label_arr[i] = 1;
		i++;
	}
	return (label_arr);
}

int	validate_label(int	*label_arr)
{
	int	i;

	i = 0;
	while (label_arr && label_arr[i])
	{
		if (label_arr[i] == 2 || label_arr[i] == 3)
		{
			(void)i;
			// if (i != 0 && (label_arr[i - 1] == 2 || label_arr[i - 1] == 3))
				// to_exit(my_vars);
			// if (i < (len(label_arr) - 1) && (label_arr[i + 1] == 2 ||
			// 	label_arr[i + 1] == 3))
			// 	to_exit(my_vars);
		}
	}
}

int main(int ac, char **av, char **env)
{
	t_vars	my_vars;

	(void)ac;
	(void)av;
	// my_vars.env = extract_env(env);
	// arr_print(env);
	while (1)
	{
		// my_vars.line = input_reader();
		my_vars.line = readline("\nLeak your thoughts > ");
		// if (my_vars.line == NULL)
		// 	to_exit(my_vars);
		if (my_vars.line[0])
			add_history(my_vars.line);
		my_vars.arg_arr = split_input_words(my_vars.line);
		// TODO: add a function that assign labels to words
		my_vars.label_arr = labelizing(my_vars);
		// TODO: add a validation function based on the labels
		// if (!validate_label(my_vars.label_arr))
		// 	to_exit(my_vars);
		// TODO: add a parsing function that split each command in a node in a linked list

		// ft_putstr(my_vars.line);
		if (my_vars.arg_arr)
			arr_print(my_vars.arg_arr);
		arr_free(my_vars.arg_arr);
		free(my_vars.line);
	}
	return (0);
}
