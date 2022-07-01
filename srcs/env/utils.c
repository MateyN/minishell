/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:28:55 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/30 15:35:49 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_index(char *key)
{
    int     i;
    char    **tmp;

    i = -1;
    while (g_ms.env_p[++i])
    {
        tmp = ft_split(g_ms.env_p[i], '=');
        if (!ft_strncmp(tmp[0], key, ft_strlen(key) + 1))
        {
            free(tmp);
            return (i);
        }
        free(tmp);
    }
    return (1);
}

int check_env_key(char *key)
{
    int i;

    i = 0;
    if (!ft_isalpha(key[i]) && key[i] != '_')
        return (FALSE);
    else
        i++;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
        return (FALSE);
        i++;
    }
    return (TRUE);
}