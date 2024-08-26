/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:04:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/27 01:13:26 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void exec_pipex(t_pipex *pipex)
{
    int pipe_fds[2];
    pid_t pid;

    if (pipe(pipe_fds) == -1)
        handle_error("Failed to create pipe");

    pid = fork();
    
    if (pid == -1)
        handle_error("Fork Failed");

    if (pid == 0)
    {
        dup2(pipex->in_fd, STDIN_FILENO);
        dup2(pipe_fds[1], STDOUT_FILENO);
        close(pipe_fds[0]);
        execve(pipex->cmd_paths[0], pipex->cmd_args[0], NULL);
        handle_error("Execve Failed");
    }
    else
    {
        waitpid(pid, NULL, 0);
        close(pipe_fds[1]);
        pipex->in_fd = pipe_fds[0];
    }
}


void ft_init_pipex(t_pipex *pipex)
{
    pipex->in_fd = -1;
    pipex->out_fd = -1;
    pipex->here_doc = 0;
    pipex->is_invalid_infile = 0;
    pipex->cmd_paths = NULL;
    pipex->cmd_args = NULL;
    pipex->cmd_count = 0;
}

void free_resources(int *pipes, int pipe_count)
{
    for (int i = 0; i < pipe_count; i++)
        close(pipes[i]);
    free(pipes);
}
