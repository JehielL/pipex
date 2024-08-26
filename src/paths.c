/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:04:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/27 01:30:49 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char *get_path_env(char **envp);
static char *check_command_in_paths(char **paths, const char *command);

char *find_command_path(const char *cmd, char **envp)
{
    char **paths;
    char *path_env;
    char *result;

    // Obtener el PATH del entorno
    path_env = get_path_env(envp);
    if (!path_env)
        return NULL;

    // Dividir el PATH en partes usando ':' como delimitador
    paths = ft_split(path_env, ':');
    if (!paths)
    {
        free(path_env); // Liberar path_env si ft_split falla
        handle_error("Failed to parse PATH");
    }

    // Buscar el comando en los paths
    result = check_command_in_paths(paths, cmd);

    // Liberar memoria de paths y path_env
    free_2d_array(paths);
    free(path_env);

    return result;
}

static char *get_path_env(char **envp)
{
    int i = 0;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return envp[i] + 5;
        i++;
    }
    return NULL;
}

static char *check_command_in_paths(char **paths, const char *command)
{
    char *full_path;
    int i;

    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        if (!full_path)
            handle_error("Failed to allocate memory for full_path");

        char *temp = ft_strjoin(full_path, command);
        free(full_path);

        if (!temp)
            handle_error("Failed to allocate memory for temp");

        full_path = temp;

        if (access(full_path, X_OK) == 0)
            return full_path;

        free(full_path);
        i++;
    }
    return NULL;
}



void free_2d_array(char **array)
{
    int i = 0;

    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
