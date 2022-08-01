/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:03:41 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/21 17:50:29 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    check_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
    if (!ft_strncmp("cd", cmd, 3) || !ft_strncmp("echo", cmd, 5) ||\
	!ft_strncmp("env", cmd, 4) || !ft_strncmp("exit", cmd, 5) ||\
	!ft_strncmp("export", cmd, 6) || !ft_strncmp("pwd", cmd, 4) ||\
	!ft_strncmp("unset", cmd, 6))
        	return (TRUE);
    return (FALSE);
}

int     exec_builtin(char **av, int flag)
{
	if (!ft_strncmp(av[0], "echo", ft_strlen(av[0]) + 1))
		echo(av);/*
        else if (!ft_strncmp(command->cmd, "cd", ft_strlen(command->cmd)))
        	cd(command);
        else if (!ft_strncmp(command->cmd, "env", ft_strlen(command->cmd)))
        	env();
        else if (!ft_strncmp(command->cmd, "exit", ft_strlen(command->cmd)))
        	exit(0);
       // else if (!ft_strncmp(command->cmd, "export", ft_strlen(command->cmd)))
        //export(); //TODO
        else if (!ft_strncmp(command->cmd, "pwd", ft_strlen(command->cmd)))
        pwd();
        //else if (!ft_strncmp(command->cmd, "unset", ft_strlen(command->cmd)))
        //unset(); //TODO*/
        if (flag == FALSE)
            exit(0);
        return (SUCCESS);
}
        
