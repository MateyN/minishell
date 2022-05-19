/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:18:51 by mnikolov          #+#    #+#             */
/*   Updated: 2022/05/19 11:33:21 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "../libft/libft.h"

t_ms    g_ms;   //global

typedef struct  s_ms
{
    char    **env_p;    //env pointer
    int     exit;
}   t_ms;

//redirections

typedef struct s_cmd
{
    char    *cmd;
    char    **av;
    int     ac;
}   t_cmd;

void    cd(t_cmd *command);
void    pwd(void);
void    env(void);
void    echo(t_cmd *command);

#endif