/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:10:00 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/09 09:23:15 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// newline error

int error_print(char *token, int exit)
{
    ft_putstr_fd("MINISHELL: syntax error near unexpected token", STDERR_FILENO);
    ft_putendl_fd(token, STDERR_FILENO);
    g_ms.exit = exit;
    return (TRUE);
}

void    ft_error(void)
{
    ft_putendl_fd("MALLOC ERROR", STDERR_FILENO);
    exit(1);
}

int invalid_command(char *cmd)
{
    ft_putstr_fd("MINISHELL: ", STDERR_FILENO);
    ft_putstr_fd("cmd", STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putendl_fd("command not found", STDERR_FILENO);
    g_ms.exit = 127;
    return (FAIL);
}