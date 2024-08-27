/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:03:00 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/27 17:10:06 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
    print_error("Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

void print_error(const char *format, ...)
{
    va_list args;
    int saved_stdout;

    va_start(args, format);
    saved_stdout = dup(STDOUT_FILENO);
    dup2(STDERR_FILENO, STDOUT_FILENO);
    ft_printf(format, args); // Assuming ft_printf uses vprintf-like function
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    va_end(args);
}