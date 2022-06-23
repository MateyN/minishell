/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:03 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/09 09:04:06 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exit_handler(int av)
{
    if (av < 0)
        exit(255);
    else
        exit(av);
}

int check_exit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]) && str[i] != '-')
        	return (FALSE);
	i++;
    }
    return (TRUE);
}

void    ft_exit(t_cmd *command)
{
    if (!command->sys_call && (!command->prev || !command->prev->sys_call))
    {
        ft_putendl_fd("exit", STDERR_FILENO);
        if (!command->av[1])
        exit(127);
    }
    if (!check_exit(command->av[1]))
    {
        ft_putstr_fd("MINISHELL: exit: ", STDERR_FILENO);
        ft_putstr_fd(command->av[1], STDERR_FILENO);
        ft_putendl_fd(": error", STDERR_FILENO);
        exit(255);
    }
    else if (command->ac > 2)
    {
        ft_putendl_fd("MINISHELL: exit: too many arguments", STDERR_FILENO);
        	if (command->sys_call || (command->prev && command->prev->sys_call))
			exit(1);
		else
			g_ms.exit = 1;
		return ;
    }
    else
        exit_handler(ft_atoi(command->av[1]));
}
