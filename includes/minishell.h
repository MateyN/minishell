/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:18:51 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/30 16:36:38 by rmamison         ###   ########.fr       */
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
	int	ac;
    int     sys_call;
    struct s_cmd    *next;
    struct s_cmd    *prev;
}   t_cmd;

typedef struct s_lst
{
	struct	s_cmd	*head;
	char		**tab;
	int	nb_arg;
	int	pipe;
}	t_lst;

void    cd(t_cmd *command);
void    path_error(char *path, int file);
void    changedir(char *path, int file);
void    pwd(void);
void    env(void);
void    echo(t_lst *command);
int     check_option(t_lst *command, int j, char *option);
int		check_builtin(char *cmd);
int		exec_builtin(t_lst *command,int flag);
void    exit_handler(int av);
int     check_exit(char *str);
void    ft_exit(t_cmd *command);

/*----------------------------------------------------------------------------*/
	/*JUD HEADERS MY PART*/	

int	check_quote(char *s);
void	init_struct(t_lst *li, char **tab);
char	**lex_split(char *s, char sep);
void	double_quote(char **tab, int *j, char *s, int *i);
char	*handle_sign(char *s, int *i);
void	handle_action(t_lst *li);
/*-----------------------------------------------------------------------------*/

# endif
