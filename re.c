
t_cmd   *parsing_commands(t_info *vars)
{
    t_cmd   *head;
    char    **arr;
    int     i;
    int     fd;

    head = create_command_node(-1, -1);
    arr = vars->arg_arr;
    i = 0;
    while (arr && arr[i])
    {
        if (ft_strncmp(arr[i], "|", 2) == 0)
            last_command(head)->next = create_command_node(-1, -1);
        else if (ft_strncmp(arr[i], "<<", 3) == 0)
            i++;  // skip heredoc delimiter (implement later)
        else if (ft_strncmp(arr[i], "<", 2) == 0 && arr[i + 1])
        {
            i++;
            fd = open(arr[i], O_RDONLY);
            if (last_command(head)->infile != -1)
                close(last_command(head)->infile);
            last_command(head)->infile = fd;
        }
        else if (ft_strncmp(arr[i], ">>", 3) == 0 && arr[i + 1])
        {
            i++;
            fd = open(arr[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (last_command(head)->outfile != -1)
                close(last_command(head)->outfile);
            last_command(head)->outfile = fd;
        }
        else if (ft_strncmp(arr[i], ">", 2) == 0 && arr[i + 1])
        {
            i++;
            fd = open(arr[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (last_command(head)->outfile != -1)
                close(last_command(head)->outfile);
            last_command(head)->outfile = fd;
        }
        else
            last_command(head)->command_args = add_arg_to_arr(
                last_command(head)->command_args, &arr[i], 1, 0);
        i++;
    }
    return (head);
}
