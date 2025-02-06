/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:58:24 by jlinarez          #+#    #+#             */
/*   Updated: 2024/12/23 15:11:08 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>

<<<<<<< HEAD
typedef struct s_pipex
{
    int     in_fd;
    int     out_fd;
    char    **cmd_paths;
    char    ***cmd_args;
    int     cmd_count;
    int     here_doc;
    int     is_invalid_infile;
    char    **envp; 
}   t_pipex;

=======
// Estructura principal del proyecto
typedef struct s_pipex
{
    int     in_fd;          // Descriptor de archivo de entrada
    int     out_fd;         // Descriptor de archivo de salida
    int     fd[2];          // Pipe para redirección
    int     prev_fd;        // Descriptor de archivo del comando anterior
    int     cmd_count;      // Número de comandos
    int     cmd_index;      // Índice del comando actual
    char    **cmd_paths;    // Rutas de los comandos
    char    **cmd_args;     // Argumentos de los comandos
    char    **commands;     // Lista de comandos
    char    **envp;         // Variables de entorno
    char    outfile;
    char    infile;
}   t_pipex;
>>>>>>> 01dc7036ef6ec7d95e41f960c9be221573b152ce

// Funciones principales
void    ft_init_pipex(t_pipex *pipex);
void    process_commands(t_pipex *pipex);
void    handle_here_doc(int argc, char **argv, char **envp);
void    parse_commands(t_pipex *pipex, char **argv, char **envp);
void    execute_command_with_path(char *command, t_pipex *pipex);

// Manejo de errores
void    handle_error(const char *msg);
void    print_error(const char *format, ...);
void    display_argument_error(void);

// Gestión de recursos
void    clean_up(char **args, char *path);
void    free_resources(t_pipex *pipex);
void    close_fds(int fd[2], int prev_fd);
void    free_2d_array(char **array);

// Búsqueda de rutas y comandos
char    *find_command_path(const char *cmd, char **envp);
char    *get_path_env(char **envp);
char    *check_command_in_paths(char **paths, const char *command);

// Utilidades para here_doc
void    read_from_stdin_and_write_to_pipe(char **argv, int fd[2]);
int     open_outfile(char **argv, int argc);

// Funciones adicionales de tu librería (libft o propias)
char    **ft_split(char const *s, char c);
char    *ft_strjoin(char const *s1, char const *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
void    ft_putstr_fd(char *s, int fd);
char    *ft_strdup(const char *s1);
char    *get_next_line(int fd);

#endif
