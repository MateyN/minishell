/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:18:51 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/13 17:13:38 by rmamison         ###   ########.fr       */
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
# include <fcntl.h>
# include <limits.h> //for mac
# include "../libft/libft.h"
//# include <linux/limits.h> //header for macro PATH_MAX

/*----token----*/
# define QUOTE 1
# define S_QUOTE 2
# define D_QUOTE 3
# define REDIR_IN 4
# define HEREDOC 5
# define REDIR_OUT_S 6
# define REDIR_OUT_D 7
# define REDIR 8
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
    char        *cmd;
    char	**av;
    int		ac;
    int     	sys_call;
    struct s_cmd    *next;
    struct s_cmd    *prev;
}   t_cmd;

typedef struct s_redir{
//	int	infile;
//	int	outfile;
//	int	fd[2];
//	int	pid;
	char	**limiter;
	char	**outfile;
}	t_redir;

typedef struct s_lst
{
	struct	s_cmd	*head;
	struct	s_redir	*redir;
	char	**tab;
	int		nb_arg;
	int		redir_in; // <
	int		heredoc; // <<
	int		redir_out; // > & >>
	int		pipe;
}	t_lst;

void    cd(t_cmd *command);
void    path_error(char *path, int file);
void    changedir(char *path, int file);
void    pwd(void);
void    env(void);
void    echo(t_lst *command);
int     check_option(t_lst *command, int j, char *option);
int	check_builtin(char *cmd);
int	exec_builtin(t_lst *command,int flag);
void    exit_handler(int av);
int     check_exit(char *str);
void    ft_exit(t_cmd *command);

/*----------------------------------------------------------------------------*/
	/*JUD HEADERS MY PART*/	
void	msg_error(char *s1, char c, char *s2);
int	error_exist(char *s);
void	init_struct(t_lst *li, char **tab);
char	**lex_split(char *s, char sep);
void	double_quote(char **tab, int *j, char *s, int *i);
//char	*handle_sign(char *s, int *i);
	/*Utils_lists*/
void	handle_action(t_lst *li);
void	take_tab(t_lst *li);
void	free_tab(char	**tab);
void	free_list(t_lst *li);
void	delete_first(t_lst *li);
	/*Redirection.c SPLIT*/
void	msg_redir(char c);
int	redirection(char c);
int	count_redirection(char *s, int i);
void	write_redirection(char **p_word, char *s, int *i);
	/*treat_quote_dollar.c*/
char	*news_s_quote(char *s);
char	*news_d_quote(char *s);
void	here_doc(t_lst *li);
	/*treat_redirection*/
/*-----------------------------------------------------------------------------*/

# endif
