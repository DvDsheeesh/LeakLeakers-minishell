/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshata <melshata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:51:00 by melshata          #+#    #+#             */
/*   Updated: 2026/06/13 12:05:16 by melshata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// part 1 mandatory
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);

// part 2 mandatory
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// BONUS part
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// get_next_line
ssize_t	ll(char *s);
void	ffree(char **s1, char **s2, char **s3);
void	*nfree(char **s1, char **s2, char **s3);
char	*schr(char *s, char c);
char	*my_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>

// #include "get_next_line/get_next_line.h"
# include "libft/libft.h"


typedef struct s_vars
{
	t_list	*env;
	char	*line;
	char	*word;
	char	**arg_arr;
	char	**path_arr;
}			t_vars;

#endif




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
			i = join_arg(&word, line, i + 1, line[i]);
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			if (word)
				arg_arr = add_arg_to_arr(arg_arr, &word);
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

int main(int ac, char **av, char **env)
{
	t_vars	my_vars;

	(void)ac;
	(void)av;
	my_vars.env = extract_env(env);
	// arr_print(env);
	while (1)
	{
		// my_vars.line = input_reader();
		my_vars.line = readline("\nLeak your thoughts > ");
		// ft_putstr(my_vars.line);
		my_vars.arg_arr = parse_input(my_vars.line);
		if (my_vars.arg_arr)
			arr_print(my_vars.arg_arr);
		arr_free(my_vars.arg_arr);
		free(my_vars.line);
	}
	return (0);
}
