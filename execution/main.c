// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: halbit <halbit@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/05/31 21:06:10 by halbit            #+#    #+#             */
// /*   Updated: 2026/06/21 00:15:23 by halbit           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "../minishell.h"

// int	g_signal = 0;

// static void	handle_sigint(int sig)
// {
// 	g_signal = sig;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// static void	setup_signals(void)
// {
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);
// }

// static t_info	init_info(char **envp)
// {
// 	t_info	info;

// 	info.env = env_copy(envp);
// 	info.exit_status = 0;
// 	return (info);
// }

// static void	run_loop(t_info *info)
// {
// 	t_cmd	*cmds;
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			write(1, "exit\n", 5);
// 			break ;
// 		}
// 		if (*line)
// 			add_history(line);
// 		cmds = parse_line(line);
// 		free(line);
// 		if (!cmds)
// 			continue ;
// 		info->exit_status = execute(cmds, info);
// 		free_cmds(cmds);
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_info	info;

// 	(void)argc;
// 	(void)argv;
// 	info = init_info(envp);
// 	setup_signals();
// 	run_loop(&info);
// 	free_arr(info.env);
// 	rl_clear_history();
// 	return (info.exit_status);
// }
int	main()
{
    int fd = open("example.txt",  O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    // Always check for errors
    if (fd == -1) {
        perror("Error opening file");
        return 1;
	}
    printf("File opened successfully with descriptor: %d\n", fd);
    
    // Operations like read(fd, ...) would happen here
    
    // Always close file descriptors when finished
    close(fd);
    return 0;
}