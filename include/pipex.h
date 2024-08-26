#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>   // Para fprintf(), stderr
#include <stdlib.h>  // Para malloc(), free(), exit()
#include <unistd.h>  // Para fork(), pipe(), dup(), dup2(), execve(), close(), read(), write(), unlink()
#include <fcntl.h>   // Para open()
#include <string.h>  // Para strerror()
#include <sys/wait.h> // Para wait(), waitpid()
#include <errno.h>   // Para errno
#include "../utils/libft/libft.h"
#include "../utils/ft_printf_42/ft_printf.h"

// Estructura para almacenar información sobre el proceso
typedef struct s_pipex
{
    int in_fd;               // Descriptor de archivo de entrada
    int out_fd;              // Descriptor de archivo de salida
    int here_doc;            // Flag para indicar si se usa here_doc
    int is_invalid_infile;   // Flag para indicar si el archivo de entrada es inválido
    char **cmd_paths;        // Matriz de rutas de comandos
    char ***cmd_args;        // Matriz de argumentos de comandos
    int cmd_count;           // Contador de comandos
} t_pipex;

// Funciones para manejar la ejecución de comandos
void execute_command(const char *cmd, int input_fd, int output_fd);

// Funciones de manejo de errores
void handle_error(const char *msg);
void print_error(const char *format, ...);

// Funciones para inicializar y liberar recursos
void ft_init_pipex(t_pipex *pipex);
void free_2d_array(char **array);
void parse_commands(t_pipex *pipex, char **argv, char **envp);
void exec_pipex(t_pipex *pipex);
void init_command_storage(t_pipex *pipex);
void process_command(t_pipex *pipex, char *command, char **envp, int index);
char *find_command_path(const char *cmd, char **envp);

#endif // PIPEX_H
