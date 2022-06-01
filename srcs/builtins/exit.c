/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:03 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/01 11:30:02 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     check_exit(char *str)
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
    // if (!check_exit)
}