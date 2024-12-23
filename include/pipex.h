#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include "../utils/libft/libft.h"
#include "../utils/ft_printf_42/ft_printf.h"


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
void free_resources(t_pipex *pipex);

// Funciones para inicializar y liberar recursos
void ft_init_pipex(t_pipex *pipex);
void free_2d_array(char **array);
void parse_commands(t_pipex *pipex, char **argv, char **envp);
void exec_pipex(t_pipex *pipex);
void init_command_storage(t_pipex *pipex);
void process_command(t_pipex *pipex, char *command, char **envp, int index);
char *find_command_path(const char *cmd, char **envp);
void free_command_storage(t_pipex *pipex);
char *get_path_env(char **envp);
char *check_command_in_paths(char **paths, const char *command);



#endif // PIPEX_H
