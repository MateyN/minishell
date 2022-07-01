/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:18:51 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/30 15:33:14 by mnikolov         ###   ########.fr       */
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
//# include <linux/limits.h> //header for macro PATH_MAX
# include <limits.h> //for mac
# include "../libft/libft.h"

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

int     exec_builtin(t_cmd *command, int flag);
int     check_builtin(char *cmd);

void    cd(t_cmd *command);
void    changedir_handler(char *oldpath);
void    path_error(char *path, int file);
void    changedir(char *path, int file);

void    pwd(void);
void    env(void);

void	output_envp(void);
void	handle_export(char *av);
void	export_error(char *av);
void	update_environ(char *key, char *new_val);
void	set_new_env(char *new_val, char *key);
char	*get_nval(char *key, char *str);
char	*get_key(char *cmd, int start);
void	export(t_cmd *command);

void    echo(t_cmd *command);
int     check_option(t_cmd *command, int j, char *option);

void    exit_handler(int av);
int     check_exit(char *str);
void    ft_exit(t_cmd *command);

void    ft_error(void);

char    *get_environ(char *key);
void    join_environ(char *key, char **tmp);
int     check_env_key(char *key);
int     get_index(char *key);
void    cpy_environ(char **envp);
char    *get_environ_key(char *cmd, int start);

/*----------------------------------------------------------------------------*/
	/*JUD HEADERS MY PART*/	

int	check_quote(char *s);
char	**lex_split(const char *s, char sep);

/*-----------------------------------------------------------------------------*/

#endif
