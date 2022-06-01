/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:18:51 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/01 11:19:38 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <string.h>
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

# define SUCCESS 1
# define FAILED -1



typedef struct  s_ms
{
    char    **env_p;    //env pointer
    int     exit;
}   t_ms;

//redirections

typedef struct s_cmd
{
    char            *cmd;
    char            **av;
    int             ac;
    int             sys_call;
    struct s_cmd    *next;
    struct s_cmd    *prev;
}   t_cmd;

t_ms    g_ms;   //global

void    cd(t_cmd *command);
void    pwd(void);
void    env(void);
void    echo(t_cmd *command);

char    *minishell(char **shell);

#endif