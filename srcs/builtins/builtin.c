/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:03:41 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/14 14:41:57 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    check_builtin(char *cmd)
{
    if (!ft_strncmp("cd", cmd, 3) || !ft_strncmp("echo", cmd, 5) || \
        !ft_strncmp("env", cmd, 4) || !ft_strncmp("exit", cmd, 5) || \
        !ft_strncmp("export", cmd, 6) || !ft_strncmp("pwd", cmd, 4) || \
        !ft_strncmp("unset", cmd, 6))
        return (TRUE);
    return (FALSE);
}

int     exec_builtin(t_cmd *command, int flag)
{
	if (!ft_strncmp(command->cmd, "echo", ft_strlen(command->cmd) + 1))
		echo(command);
        else if (!ft_strncmp(command->cmd, "cd", ft_strlen(command->cmd) + 1))
        	cd(command);
        else if (!ft_strncmp(command->cmd, "env", ft_strlen(command->cmd) + 1))
        	env();
        else if (!ft_strncmp(command->cmd, "exit", ft_strlen(command->cmd) + 1))
        	exit(0);
        else if (!ft_strncmp(command->cmd, "export", ft_strlen(command->cmd) + 1))
            export(command);
        else if (!ft_strncmp(command->cmd, "pwd", ft_strlen(command->cmd) + 1))
            pwd();
        else if (!ft_strncmp(command->cmd, "unset", ft_strlen(command->cmd) + 1))
            unset(command);
        if (flag == FALSE)
            exit(0);
        return (SUCCESS);
}
        
