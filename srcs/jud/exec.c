/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:07:39 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/21 18:45:44 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_fd(int fd_in, int fd_out)
{
	if (dup2(fd_in, fd_out) < 0)
		msg_error("error: dup2\n", 0, NULL);
}

void	close_fd(t_lst *li)
{
	int	i;

	i = -1;
	while (++i < li->pipe)
		close(li->tube_fd[i]);
	if (li->infile)
		close(li->infile);
	if (li->outfile)
		close(li->outfile);
}

int	std_in_out(t_lst *li, t_redir *redir)
{
	if (redir->sign == REDIR_IN)
		li->infile = open(redir->name, O_RDONLY);
	else if (redir->sign == REDIR_OUT_S)
		li->outfile = open(redir->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	else if (redir->sign == REDIR_OUT_D)
		li->outfile = open(redir->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (li->infile < 0 || li->outfile < 0)
	{
		if (redir->sign == REDIR_IN)
		{
			msg_error("minishell: ", 0, redir->name);
			write(2, ": No such file or directory\n", 28);
		}
		else
			msg_error("Error: outfile", 0, "\n");
		return (0);
	}
	if (li->infile > 0 || li->outfile > 0)
		redir->sign = 0;
	return (1);
}

int	init_redir(t_cmd *node, t_lst *li)
{
	t_redir	*red;

	red = node->redir;
	while (red)
	{
		if (!red->sign)
			red = red->next;
		else if (push_redir(&node, &red, red->sign))
			if (!std_in_out(li, red))
				return (-1);
	}
	return (0);
}

static int	process_daddy(t_lst **li)
{
	int	status;	
	
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		int statuscod = WEXITSTATUS(status);
		if (statuscod == 0)
			;//printf("succes statcode\n");
		else
			printf("failure stat code => %d\n", statuscod);
	}
	return (1);
}

static int	process_child(t_lst *li, t_cmd node)
{	
	init_redir(&node, li);
	if (li->infile)
		dup_fd(li->infile, STDIN_FILENO);
	if (li->outfile)
		dup_fd(li->outfile, STDOUT_FILENO);
	else if (li->times == 0 && li->pipe)
		dup_fd(li->tube_fd[1], 1); //close(fd 0)
	if (li->times > 0) 
	{
		if (!li->infile)
			dup_fd(li->tube_fd[(li->times * 2) - 2], 0);
		if (li->times != li->pipe && !li->outfile)
			dup_fd(li->tube_fd[(li->times * 2) + 1], 1);
	}
	if (check_builtin(node.cmd) == TRUE)
		exec_builtin(node.av, 1);
	close_fd(li);
	exit(0);
	/*	if (execv("test_redir/test", li->head->av) == -1)
		{
			printf("soucis execv\n");
		}*/
}

int	exec_process(t_lst *li)
{
	if (li->pipe)
		init_pipe(li);
	if (count_heredoc(li))
		if (here_doc(li->head, count_heredoc(li)) == -1)
			return (-1);
	li->times = -1;
	while (++(li->times) <= li->pipe)
	{
		li->pid = fork();
		if (li->pid == -1)
			return (-1);
		else if (li->pid == 0)
			process_child(li, *li->head);
		delete_first(&li);
	}
	return (process_daddy(&li));
}
