/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:08 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/14 14:52:30 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void    unset_error(char *error)
{
    ft_putstr_fd("MINISHELL: unset: ", STDERR_FILENO);
    ft_putstr_fd(error, STDERR_FILENO);
    ft_putendl_fd(": error", STDERR_FILENO);
    g_ms.exit = 1;
    return ;
}

static void    unset_environ(int index)
{
    char    **tmp;
    int     i;
    int     j;

    tmp = (char **)malloc(sizeof(char *) * len_2ptr(g_ms.env_p));
    if (!tmp)
        return (ft_error());
    i = -1;
    j = -1;
    while (g_ms.env_p[++i])
    {
        if (i != index)
            tmp[++j] = g_ms.env_p[i];
    }
    tmp[j + 1] = NULL;
    free (g_ms.env_p[index]);
    g_ms.env_p[index] = NULL;
    free (g_ms.env_p);
    g_ms.env_p = NULL;

}

static void unset_handle(char *av)
{
    int i;

    if (!check_env_key(av))
        return (unset_error(av));
    i = get_index(av);
    if (i >= 0)
        unset_environ(i);
}

void    unset(t_cmd *command)
{
    int i;

    i = 0;
    g_ms.exit = 0;
    while (command->av[++i])
        unset_handle(command->av[i]);
}