/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:07:01 by mnikolov          #+#    #+#             */
/*   Updated: 2022/05/19 12:09:41 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    env(void)
{
    int i;

    i = -1;
    while (g_ms.env_p[++i])
    {
        if (ft_strchr(g_ms.env_p[i], '='))
            printf("%s\n", g_ms.env_p[i]);
    }
    g_ms.exit = 0;
    return ;
}