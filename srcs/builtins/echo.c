/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:03:26 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/21 17:47:56 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_option(char **av, int j, char *option)
{
    int i;

    	if (av[j] == NULL)
        	return (0);
    	if (av[j][0] != '-')
        	return (0);
    	if (!ft_strncmp("-n", av[j], 3))
    	{		
        	*option = 'n';
        	return (1);
	}	
    	i = 1;
	while (av[j][i])
	{
		if (av[j][i] != 'n')
			return (0);
		i++;
	}
	*option = av[j][i - 1];
	if (*option == 'n')
		return (1);
	return (0);
}

void    echo(char **av)
{
    char    option;
    int     i;
    int	fd;
	
    i = 0;
    option = 0;
    while (av[++i])
    {
        while (check_option(av, i, &option))
            i++;
        if (av[i] == NULL)
            break ;
        printf(av[i]);
        if (av[i] != NULL)
            printf(" ");
       	g_ms.exit = 0;
    }
    if (i > 0)
	printf("\n");
    return ;
}
