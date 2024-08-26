/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:03:00 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/27 01:15:20 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void handle_error(const char *msg)
{
    print_error("Error: %s\n", msg);  // Usa 'msg' para mostrar el mensaje de error.
    exit(EXIT_FAILURE);
}

void print_error(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Redirige stdout a stderr
    int saved_stdout = dup(STDOUT_FILENO);
    dup2(STDERR_FILENO, STDOUT_FILENO);

    // Imprime el mensaje de error usando ft_printf
    ft_printf(format, args);

    // Restaura stdout
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    va_end(args);
}

