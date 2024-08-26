/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:04:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/26 22:11:41 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_command(const char *cmd, int input_fd, int output_fd) {
    pid_t pid = fork();
    if (pid == -1) {
        handle_error("fork");
    }
    if (pid == 0) { // Proceso hijo
        if (dup2(input_fd, STDIN_FILENO) == -1 || dup2(output_fd, STDOUT_FILENO) == -1) {
            handle_error("dup2");
        }
        close(input_fd);
        close(output_fd);
        char *const args[] = {"/bin/sh", "-c", (char *)cmd, NULL};
        execve("/bin/sh", args, NULL);
        handle_error("execve");
    }
}

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void free_resources(int *pipes, int pipe_count) {
    for (int i = 0; i < pipe_count; ++i) {
        close(pipes[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s infile command1 command2 outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        handle_error("pipe");
    }

    int infile = open(argv[1], O_RDONLY);
    if (infile == -1) {
        handle_error("open infile");
    }

    int outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile == -1) {
        handle_error("open outfile");
    }

    execute_command(argv[2], infile, pipefd[1]);
    close(pipefd[1]); // Cerrar el extremo de escritura del pipe en el proceso padre

    execute_command(argv[3], pipefd[0], outfile);
    close(pipefd[0]); // Cerrar el extremo de lectura del pipe en el proceso padre

    close(infile);
    close(outfile);

    // Esperar a que terminen los procesos hijos
    wait(NULL);
    wait(NULL);

    return 0;
}
