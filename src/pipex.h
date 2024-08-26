#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>   // Para fprintf(), stderr
#include <stdlib.h>  // Para malloc(), free(), exit()
#include <unistd.h>  // Para fork(), pipe(), dup(), dup2(), execve(), close(), read(), write(), unlink()
#include <fcntl.h>   // Para open()
#include <string.h>  // Para strerror()
#include <sys/wait.h> // Para wait(), waitpid()

// Función para ejecutar un comando en un proceso hijo
void execute_command(const char *cmd, int input_fd, int output_fd);

// Función para manejar errores e imprimir mensajes
void handle_error(const char *msg);

// Función para cerrar los descriptores de archivo del pipe
void free_resources(int *pipes, int pipe_count);

#endif // PIPEX_H
