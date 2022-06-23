/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:03:26 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/09 09:03:36 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ms g_ms;

int check_option(t_cmd *command, int j, char *option)
{
    int i;

    if (command->av[j] == NULL)
        return (0);
    if (command->av[j][0] != '-')
        return (0);
    if (!ft_strncmp("-n", command->av[j], 3))
    {
        *option = 'n';
        return (1);
    }	
    i = 1;
	while (command->av[j][i])
	{
		if (command->av[j][i] != 'n')
			return (0);
		i++;
	}
	*option = command->av[j][i - 1];
	if (*option == 'n')
		return (1);
	return (0);
}

void    echo(t_cmd *command)
{
    char    option;
    int     i;
    //int     str;

    i = 0;
    //str = 0;
    option = 0;
    while (command->av[++i])
    {
        while (check_option(command, i, &option))
            i++;
        if (command->av[i] == NULL)
            break ;
        printf("%s", command->av[i]);
        if (command->av[i] != NULL)
            printf(" ");
        g_ms.exit = 0;
        return ;
    }
}
