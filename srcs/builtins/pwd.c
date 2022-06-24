/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:00 by mnikolov          #+#    #+#             */
/*   Updated: 2022/05/25 13:49:09 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    pwd(void)
{
    //char    *pwd;

    printf("%s\n", getcwd(0, PATH_MAX));
    //free(pwd);
    //pwd = NULL;
    g_ms.exit = 0;
    return ;
}
