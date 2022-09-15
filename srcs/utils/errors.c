/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:10:00 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/11 22:29:51 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int error_print(char *token, int exit)
{
    ft_putstr_fd("MINISHELL: syntax error near unexpected token", STDERR_FILENO);
    ft_putendl_fd(token, STDERR_FILENO);
    g_ms.exit = exit;
    return (TRUE);
}

void	ft_error(char *func, char *str)
{
	ft_putstr_fd("bash-3.2: ", STDOUT_FILENO);
	ft_putstr_fd(func, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putchar_fd('`', STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
}
/*
int invalid_command(char *cmd)
{
	(void) cmd;
    ft_putstr_fd("MINISHELL: ", STDERR_FILENO);
    ft_putstr_fd("cmd", STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putendl_fd("command not found", STDERR_FILENO);
    g_ms.exit = 127;
    return (FAIL);
}
*/
