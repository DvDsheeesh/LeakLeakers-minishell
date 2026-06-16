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


typedef struct s_vars
{
	// t_list	*env;
	char	*line;
	char	*word;
	char	**arg_arr;
	char	**label_arr;
}			t_vars;
