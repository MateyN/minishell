/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:55:29 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/17 17:08:34 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//env_2_str convert env list to env tab
void	rl_replace_line(const char *text, int clear_undo);


static void	check_error(char *path)
{
	struct	stat	sb;
	int		i;
	char		*t;
	
	i = 0;
	msg_error("minishell: ", 0, path);
	if (path[ft_strlen(path) - 1] == '/')
	{
		t = malloc(sizeof(char) * (ft_strlen(path) - 1));
		if (!t)
			return ;
		ft_strlcpy(t, path, ft_strlen(path));
		path = t;
		i = 1;
	}
	if (stat(path, &sb) == -1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if(sb.st_mode & S_IFDIR)
		ft_putstr_fd(": Is a directory\n", 2);
	else if(sb.st_mode & S_IFREG)
	{
		if (i == 1)
		{
			ft_putstr_fd(": Not a directory\n", 2);
			free(t);
		}
		else
			ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (i == 1)
		free(t);
	exit(127);
}

static int	ft_exec(t_cmd *node, t_lst *li, pid_t *pid)
{
	struct	stat	sb;
	char	**tab;
	int	i;

	tab = NULL;
	if (!ft_strchr(node->cmd, '/'))
	{
		take_path(&tab, node->cmd, li);
		if (!tab)
		{
			msg_error("minishell: ", 0, node->cmd);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(127);
		}
		i = -1;
		while (tab[++i] && access(tab[i], X_OK) != 0)
			;
		if (!tab[i])
		{
			free_tab(tab);
			return (0);
		}
		node->cmd = ft_strdup(tab[i]);
		free_tab(tab);
	}	
	tab =  env_2_str(li);
	if (execve(node->cmd, node->av, tab) == -1)
	{
		if (ft_strchr(node->cmd, '/'))
			check_error(node->cmd);
		free_tab(tab);
		return (0);
		//exit(EXIT_FAILURE);
	}
	return(1);
}

static int	process_daddy(t_lst **li, pid_t *pid)
{
	int	status;
	int	i;

	i = -1;
	close_fd(NULL, li);
	while (++i <= (*li)->pipe)
	{
		g_ms.pid_sig = pid[i];
		init_signals();
		waitpid(pid[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit :3\n", 8);
			else if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			g_ms.exit = 128 + status;
		}
		if (WIFEXITED(status))
			g_ms.exit = WEXITSTATUS(status);
		g_ms.pid_sig = 0;
	}
	return (1);
}

static int	process_child(t_lst *li, t_cmd node, int times, pid_t *pid)
{
	child_signal(0);
	if (node.infile)
		dup_fd(node.infile, STDIN_FILENO);
	if (node.outfile)
		dup_fd(node.outfile, STDOUT_FILENO);
	if (times == 0 && li->pipe && !node.outfile)
		dup_fd(li->tube_fd[times][1], 1); //close(fd 0)
	if (times > 0)
	{
		if (!node.infile)
			dup_fd(li->tube_fd[times - 1][0], 0);
		if (times != li->pipe && !node.outfile)
			dup_fd(li->tube_fd[times][1], 1);
	}
	close_fd(&node, &li);
	if (check_builtin(node.cmd) == TRUE)
		exec_builtin(&node, li);
	else if (node.cmd && !ft_exec(&node, li, &pid[times]))
	{
		msg_error("minishell: ", 0, node.av[0]);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	exit(0);
}

int	exec_process(t_lst *li)
{
	int		status;	
	int		ret;
	int		times;
	pid_t		pid[li->pipe + 1];

	if (li->pipe)
		init_pipe(li);
	times = -1;
	while (++times <= li->pipe)
	{
		pid[times] = fork();
		if (pid[times] == -1)
			return (-1);
		else if (pid[times] == 0)
		{
			if (li->redirection)
				init_redir(li->head, li);
			process_child(li, *li->head, times, pid);
		}
		
		delete_first(&li);
	}
	unlink(".heredoc");
	return (process_daddy(&li, pid));
}
