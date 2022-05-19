/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:33:24 by mnikolov          #+#    #+#             */
/*   Updated: 2022/05/19 12:03:13 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
void    handler()
{
    ...
}
void    path error()
{
    ...
}

void    changedir(char *path)
{
    char    *old_path;

    old_path = getcwd();
    if (chdir(path) == 0)
        ...
    else
        path error
    free path
}
*/
void    cd(t_cmd *command)
{
    char    *home;
    int     file;
    struct stat buff;

    home = get_env("HOME");
    file = FALSE;
    if(command->ac == 1)
        // change directory
    else
    {
        if(stat(command->av[1], &buff) == 0)
        file == TRUE;
        // change directory
    }
    free(home);
    home = NULL;
    return ;
}