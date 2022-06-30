/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:28:34 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/10 12:34:41 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    sigint_handler(int sig)
{
    if (sig == SIGINT)
    {
        rl_on_new_line();
        rl_redisplay();
        printf(" \n");
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
        g_ms.exit = 1;
    }
}

void    init_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}