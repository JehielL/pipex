/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:04:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/27 17:11:57 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int argc, char *argv[], char *envp[])
{
    t_pipex pipex;

    if (argc != 5)
    {
        print_error("Usage: %s infile command1 command2 outfile\n", argv[0]);
        return (EXIT_FAILURE);
    }
    ft_init_pipex(&pipex);
    pipex.in_fd = open(argv[1], O_RDONLY);
    if (pipex.in_fd == -1)
        handle_error("Error opening infile");
    pipex.out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex.out_fd == -1)
    {
        close(pipex.in_fd);
        handle_error("Error opening outfile");
    }
    pipex.cmd_count = 2;
    parse_commands(&pipex, argv, envp);
    exec_pipex(&pipex);
    close(pipex.out_fd);
    free_resources(&pipex);
    return (0);
}



