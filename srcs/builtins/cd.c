/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:33:24 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/15 11:05:20 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    path_error(char *path, int file)
{
    if (file)
    {
        ft_putstr_fd("MINISHELL: cd: ", STDERR_FILENO);
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putendl_fd(": not a directory", STDERR_FILENO);
    }
    else
    {
        ft_putstr_fd("MINISHELL: cd: ", STDERR_FILENO);
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putendl_fd(strerror(2), STDERR_FILENO);
    }
    g_ms.exit = 1;
}
void    changedir(char *path, int file)
{
    char    *old_path;
    old_path = getcwd(0, _PC_PATH_MAX);
    if (chdir(path) == 0)
    //    chdir_handler(old_path);
    else
        path_error(path, file);
    free(old_path);
    old_path = NULL;
    return ;
}

void    cd(t_cmd *command)
{
    char    *home;
    int     file;
    struct stat buff;

    home = getenv("HOME=");
    file = FALSE;
    if(command->ac == 1)
        changedir(home, file);
    else
    {
        if(stat(command->av[1], &buff) == 0)
        file = TRUE;
        changedir(home, file);
    }
    free(home);
    home = NULL;
    return ;
}