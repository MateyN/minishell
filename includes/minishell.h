/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:18:51 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/21 18:40:52 by rmamison         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <limits.h> //for mac
# include "../libft/libft.h"
//# include <linux/limits.h> //header for macro PATH_MAX

/*----token----*/
# define QUOTE 1
# define S_QUOTE 2
# define D_QUOTE 3
# define DOLLAR 4
# define REDIR_IN 5
# define HEREDOC 6
# define REDIR_OUT_S 7
# define REDIR_OUT_D 8
# define REDIR 9
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
    char    		*cmd;
    char		**av;
    int			ac;
    int			fd_file;
    int			infile; // < & <<
    int			outfile; // > & >>
    int     		sys_call;
    struct s_redir	*redir;
    struct s_cmd    	*next;
    struct s_cmd    	*prev;
}   t_cmd;

typedef struct s_redir{
	int 	pos; 
	int	sign;
	char	*name;
	struct	s_redir	*next;
}	t_redir;

typedef struct s_lst
{
	struct	s_cmd	*head;
	char	**tab;
	int		nb_arg;
	int		redirection;
	int		pipe;
	int		pid;
	int		**tube_fd;
	int		times;
}	t_lst;

void    cd(t_cmd *command);
void    path_error(char *path, int file);
void    changedir(char *path, int file);
void    pwd(void);
void    env(void);
void    echo(char **av);
int     check_option(char **av, int j, char *option);
int		check_builtin(char *cmd);
int		exec_builtin(char **av,int flag);
void    exit_handler(int av);
int     check_exit(char *str);
void    ft_exit(t_cmd *command);

/*----------------------------------------------------------------------------*/
//JUD
	/*handle_input.c*/
void	msg_error(char *s1, char c, char *s2);
int	error_exist(char *s);
void	init_struct(t_lst *li, char **tab);
	
	/*lexical_split.c && redirection.parse*/
int	redirection(char c);
int	count_redirection(char *s, int i);
void	write_redirection(char **p_word, char *s, int *i);
char	**lex_split(char *s, char sep);

	/*analyse_lexical.c*/
int	quote_exist(char *s);
int	redir_exist(char *s);
void	handle_action(t_lst *li);	
	/*treat_quote_dollar.c*/
char	*news_s_quote(char *s);
char	*news_d_quote(char *s);

	/*list_utils.c*/
void	create_list(t_lst *li);
void	delete_first(t_lst **li);
	
	/*init_redirection.c && init_pipe*/
void	init_pipe(t_lst *li);
int	init_redir(t_cmd *node, t_lst *li);	
	/*here_doc*/
int	here_doc(t_redir *red);	

	/*exec.c && exec_utils.c*/
void	dup_fd(int fd_in, int fd_out);
void	close_fd(t_cmd *node, t_lst **li);
void	*take_path(char ***dest, char *cmd);
int	exec_process(t_lst *li);
	
	/*free_utils.c*/
void	free_all(t_lst *li);
void	free_list(t_lst *li);
void	free_tab(char **tab);
void	free_pipe(t_lst *li);
void	print_list(t_lst *li);


/*-----------------------------------------------------------------------------*/

# endif
