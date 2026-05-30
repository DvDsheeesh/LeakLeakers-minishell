#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>

// #include "get_next_line/get_next_line.h"
#include "libft/libft.h"


// typedef struct s_vars
// {
// 	void			*content;
// 	struct s_vars	*next;
// }					t_vars;


void	arr_free(char **arg_arr)
{
	int	i;

	i = 0;
	while (arg_arr && arg_arr[i++])
		free(arg_arr[i - 1]);
	free(arg_arr);
}

int len(char *str)
{
	int	l;

	l = 0;
	if (str)
		while(str[l])
			l++;
	return l;
}

int	arr_len(char **arr)
{
	int	l;

	l = 0;
	if (arr)
		while(arr[l])
			l++;
	return l;
}

//#############################################

static char	*extend_str(char *s1, char c)
{
	char	*ss;
	size_t	i;

	ss = malloc(len(s1) + 2);
	if (!ss)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			ss[i] = s1[i];
			i++;
		}
	}
	free(s1);
	ss[i++] = c;
	ss[i] = '\0';
	return (ss);
}

char	*ms_join(char *s1, char *s2)
{
	char	*ss;
	ssize_t	i;
	ssize_t	j;

	ss = malloc(len(s1) + len(s2) + 1);
	if (!ss)
		return (NULL);
	i = 0;
	if (s1 && (i-- || 1))
		while (s1[++i])
			ss[i] = s1[i];
	if (s1)
		free(s1);
	j = 0;
	if (s2)
		while (s2[j] && s2[j] != '\n')
			ss[i++] = s2[j++];
	ss[i] = '\0';
	return (ss);
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
		return;
	while(str && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int has_new_line(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		if (str[i++] == '\n')
			return (1);
	return (0);
}

char	*input_reader()
{
	char	*buff;
	char	*str;
	int		rb;
	
	buff = malloc(6);
	buff[0] = '\0';
	str = ms_join(NULL, NULL);
	while(buff && !has_new_line(buff))
	{
		rb = read(0, buff, 5);
		buff[rb] = '\0';
		str = ms_join(str, buff);
	}
	free(buff);
	return (str);
}

//#############################################

char	*ms_cpy(char *s1)
{
	char	*ss;
	int		i;
	int		j;

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
	printf("i is : %d\n", i);
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
	if (word)
	{
		while (word[i])
		{
			new_word[i] = word[i];
			i++;
		}
	}
	// while (word && word[i])
	// {
	// 	new_word[i] = word[i];
	// 	i++;
	// }
	// while (word && word[i++])
	// 	new_word[i - 1] = word[i - 1];  // might have leaks
	free(word);
	new_word[i++] = c;
	new_word[i] = '\0';
	return (new_word);
}

int	join_arg(char **word, char *line, int i, char end_char)
{
	while (line[i] != end_char)
		*word = extend_arg(*word, line[++i]);
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

char	**parse_input(char *line)
{
	int	i;
	char	*word;
	char	**arg_arr;

	i = 0;
	word = NULL;
	arg_arr = NULL;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = join_arg(&word, line, i, line[i]);
		else if (isprint(line[i]) && !isspace(line[i]))
			word = extend_arg(word, line[i]);
		if ((isspace(line[i]) || line[i + 1] == '\0') && word)
		{
			arg_arr = add_arg_to_arr(arg_arr, &word);
			printf("is_space, new word: %s\n", arg_arr[arr_len(arg_arr) - 1]);
		}
		i++;
	}
	// if (word)
	// 	free(word);
	return (arg_arr);
}

void	arr_print(char **arr)
{
	int	i;
	int	j;

	i = 0;
	printf("arr: %p\n", arr);
	// printf("arr[0]: %s", arr[0]);
	while (arr && arr[i])
	{
		// ftpf_putnbr(i, 0);
		ft_putstr(arr[i++]);
	}
}

int main(int ac, char **av)
{
	char	*text;
	char	**arg_arr;
	char	**path_arr;

	text = NULL;
	path_arr = NULL;
	while (1)
	{
		// text = input_reader();
		text = readline("\nLeak your thoughts > ");
		// ft_putstr(text);
		arg_arr = parse_input(text);
		if (arg_arr)
			arr_print(arg_arr);
		arr_free(arg_arr);
		free(text);
	}
	return (0);
}


// {
// 	path = ["Desktop/A", "Desktop/b", "Desktop/A/B"];
// 	command = ["ls", "-l", "|", "grep", "-n", "file1"];
// }