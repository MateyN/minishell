/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:00 by mnikolov          #+#    #+#             */
/*   Updated: 2022/05/19 12:11:45 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    pwd(void)
{
    char    *pwd;

    pwd = getcwd();
    printf("%s\n", pwd);
    free(pwd);
    pwd = NULL;
    g_ms.exit = 0;
    return ;
}