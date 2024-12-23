/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:00:16 by jlinarez          #+#    #+#             */
/*   Updated: 2024/12/23 15:11:31 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void handle_here_doc(int argc, char **argv, char **envp)
{
    int here_doc_pipe[2];
    t_pipex pipex;

    if (argc < 6)
        display_argument_error();
    if (pipe(here_doc_pipe) == -1)
        handle_error("ERROR: failed to create pipe");
    read_from_stdin_and_write_to_pipe(argv, here_doc_pipe);
    pipex.outfile = open_outfile(argv, argc);
    pipex.infile = here_doc_pipe[0];
    pipex.prev_fd = -1;
    pipex.cmd_count = argc - 4;
    pipex.commands = &argv[3];
    pipex.envp = envp;
    pipex.cmd_index = 0;
    process_commands(&pipex);
    close(here_doc_pipe[0]);
}
static void read_from_stdin_and_write_to_pipe(char **argv, int fd[2])
{
    char *line;

    while (1)
    {
        ft_putstr_fd("pipe heredoc> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0
            && line[ft_strlen(argv[2])] == '\n')
            break;
        ft_putstr_fd(line, fd[1]);
        clean_up(NULL, line);
    }
    clean_up(NULL, line);
    close(fd[1]);
}
