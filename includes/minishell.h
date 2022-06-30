/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:18:51 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/24 18:00:49 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <sys/stat.h>
# include <limits.h> //for mac
# include "../libft/libft.h"
//# include <linux/limits.h> //header for macro PATH_MAX

/*--------MACRO-COLOR------------------*/
#define BOLDGREEN   "\033[1m\033[36m"   
#define RESET "\033[m" //white color
/*-----------------------------------*/

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAIL -1


typedef struct  s_ms
{
    char    **env_p;    //env pointer
    int     exit;
}   t_ms;

extern t_ms    g_ms;   //global
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


void    cd(t_cmd *command);
void    path_error(char *path, int file);
void    changedir(char *path, int file);
void    pwd(void);
void    env(void);
void    echo(t_cmd *command);
int     check_option(t_cmd *command, int j, char *option);
int		check_builtin(char *cmd);
int		exec_builtin(t_cmd *command,int flag);
void    exit_handler(int av);
int     check_exit(char *str);
void    ft_exit(t_cmd *command);

/*----------------------------------------------------------------------------*/
	/*JUD HEADERS MY PART*/	

typedef struct s_node{
	char	*
}
int	check_quote(char *s);
char	**lex_split(const char *s, char sep);

/*-----------------------------------------------------------------------------*/

# endif
