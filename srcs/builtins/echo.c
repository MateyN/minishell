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

int check_option(t_lst *command, int j, char *option)
{
    int i;

    	if (command->tab[j] == NULL)
        	return (0);
    	if (command->tab[j][0] != '-')
        	return (0);
    	if (!ft_strncmp("-n", command->tab[j], 3))
    	{		
        	*option = 'n';
        	return (1);
	}	
    	i = 1;
	while (command->tab[j][i])
	{
		if (command->tab[j][i] != 'n')
			return (0);
		i++;
	}
	*option = command->tab[j][i - 1];
	if (*option == 'n')
		return (1);
	return (0);
}

void    echo(t_lst *command)
{
    char    option;
    int     i;
    //int     str;

    i = 0;
    //str = 0;
    option = 0;
    while (command->tab[++i])
    {
        while (check_option(command, i, &option))
            i++;
        if (command->tab[i] == NULL)
            break ;
        printf("%s", command->tab[i]);
        if (command->tab[i] != NULL)
            printf(" ");
       	g_ms.exit = 0;
    }
    if (i > 0)
	printf("\n");
    return ;
}
