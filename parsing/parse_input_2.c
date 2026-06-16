#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_vars	my_vars;

	(void)ac;
	(void)av;
	my_vars.env = extract_env(env);
	while (1)
	{
		my_vars.line = readline("\nLeak your thoughts > ");
		my_vars.arg_arr = parse_input(my_vars.line);
		if (my_vars.arg_arr)
			arr_print(my_vars.arg_arr);
		arr_free(my_vars.arg_arr);
		free(my_vars.line);
	}
	return (0);
}