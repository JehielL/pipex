/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:04:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/27 17:25:59 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void free_command_storage(t_pipex *pipex)
{
    int i;

    if (pipex->cmd_args)
    {
        i = 0;
        while (i < pipex->cmd_count)
        {
            if (pipex->cmd_args[i])
                free_2d_array(pipex->cmd_args[i]);
            i++;
        }
        free(pipex->cmd_args);
    }
    if (pipex->cmd_paths)
        free_2d_array(pipex->cmd_paths);
}

void init_command_storage(t_pipex *pipex)
{
    int i;

    pipex->cmd_args = malloc(sizeof(char *) * (pipex->cmd_count + 1)); // +1 for NULL termination
    pipex->cmd_paths = malloc(sizeof(char *) * (pipex->cmd_count + 1)); // +1 for NULL termination
    if (!pipex->cmd_args || !pipex->cmd_paths)
    {
        free_command_storage(pipex);
        handle_error("Failed to allocate memory for command storage");
    }
    i = 0;
    while (i < pipex->cmd_count)
    {
        pipex->cmd_args[i] = NULL;
        pipex->cmd_paths[i] = NULL;
        i++;
    }
    // Ensure NULL termination
    pipex->cmd_args[pipex->cmd_count] = NULL;
    pipex->cmd_paths[pipex->cmd_count] = NULL;
}


void parse_commands(t_pipex *pipex, char **argv, char **envp)
{
    int i;

    init_command_storage(pipex);
    i = 0;
    while (i < pipex->cmd_count)
    {
        process_command(pipex, argv[i + 2], envp, i);
        i++;
    }
}

void process_command(t_pipex *pipex, char *command, char **envp, int index)
{
    pipex->cmd_args[index] = ft_split(command, ' ');
    if (!pipex->cmd_args[index])
    {
        free_command_storage(pipex);
        handle_error("Failed to parse command");
    }
    pipex->cmd_paths[index] = find_command_path(pipex->cmd_args[index][0], envp);
    if (!pipex->cmd_paths[index])
    {
        free_command_storage(pipex);
        handle_error("Command not found");
    }
}
