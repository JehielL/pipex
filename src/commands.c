/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:04:44 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/27 01:28:59 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void init_command_storage(t_pipex *pipex)
{
    int i;

    pipex->cmd_args = malloc(sizeof(char *) * pipex->cmd_count);
    pipex->cmd_paths = malloc(sizeof(char *) * pipex->cmd_count);

    if (!pipex->cmd_args || !pipex->cmd_paths)
        handle_error("Failed to allocate memory for command storage");

    // Inicializar las matrices a NULL
    i = 0;
    while (i < pipex->cmd_count)
    {
        pipex->cmd_args[i] = NULL;
        pipex->cmd_paths[i] = NULL;
        i++;
    }
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
        handle_error("Failed to parse command");

    pipex->cmd_paths[index] = find_command_path(pipex->cmd_args[index][0], envp);

    if (!pipex->cmd_paths[index])
        handle_error("Command not found");
}

