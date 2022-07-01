/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:08 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/30 16:13:12 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    unset_error(char *error)
{
    ft_putstr_fd("MINISHELL: unset: ", STDERR_FILENO);
    ft_putstr_fd(error, STDERR_FILENO);
    ft_putendl_fd(": error", STDERR_FILENO);
    g_ms.exit = 1;
    return ;
}

void    unset_environ(int index)
{
    char    *tmp;
    int     i;
    int     len;

    tmp = (char **)malloc(sizeof(g_ms.env_p[i]) * len + 1)
    
}