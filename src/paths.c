/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:04:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/27 17:25:42 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char *get_path_env(char **envp);
char *check_command_in_paths(char **paths, const char *command);

char *find_command_path(const char *cmd, char **envp)
{
    char **paths;
    char *path_env;
    char *result;

    path_env = get_path_env(envp);
    if (!path_env)
        return NULL;
    paths = ft_split(path_env, ':');
    if (!paths)
    {
        handle_error("Failed to parse PATH");
    }
    result = check_command_in_paths(paths, cmd);
    free_2d_array(paths);
    return result;
}

char *get_path_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (envp[i] + 5);
        i++;
    }
    return (NULL);
}

char *check_command_in_paths(char **paths, const char *command)
{
    char *full_path;
    char *temp;
    int i;

    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        if (!full_path)
            handle_error("Failed to allocate memory for full_path");
        temp = ft_strjoin(full_path, command);
        free(full_path);
        if (!temp)
            handle_error("Failed to allocate memory for temp");
        if (access(temp, X_OK) == 0)
            return (temp);
        free(temp);
        i++;
    }
    return (NULL);
}

void free_2d_array(char **array)
{
    int i;

    if (!array)
        return;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
