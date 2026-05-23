#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

#include "get_next_line/get_next_line.h"

int len(char *str)
{
	int	l;

	l = 0;
	if (str)
		while(str[l])
			l++;
	return l;
}

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

int main(int ac, char **av)
{
	char *text;

	while (1)
	{
		// text = input_reader();
		text = readline("gemme you blyat task > ");
		ft_putstr(text);
		free(text);
	}
}
