/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:08 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/09 09:04:46 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    unset_error(char *error)
{
    ft_putstr_fd("MINISHELL: unset: ", STDERR_FILENO);
    ft_putstr_fd(error, STDERR_FILENO);
    ft_putendl_fd(": error", STDERR_FILENO);
    g_ms.exit = 1;
    return ;
}