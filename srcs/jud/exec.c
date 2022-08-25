/* ************************************************************************** */

/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:07:39 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/21 18:45:44 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_exec(t_cmd *node)
{
	char 	**tab;
	int	i;

	tab = NULL;
	take_path(&tab, node->cmd);
	i = -1;
	while(tab[++i])
	{
		if (!access(tab[i], X_OK))
		{
			node->cmd = tab[i];
			if (execve(node->cmd, node->av, g_ms.env_p) == -1)
			{
				free_tab(tab);
				exit(1);
			}
			free_tab(tab);
			return (1);
		}
	}
	free_tab(tab);
	return (0);
}

static int	process_daddy(t_lst **li)
{
	int	status;
	int	statuscod;	
	int	i;

	i = -1;
	while (++i <= (*li)->pipe)
	{
		waitpid(-1, &status, WCONTINUED);
		if (WIFEXITED(status))
		{
			statuscod = WEXITSTATUS(status);
			if (statuscod == 0)
				;//printf("succes process\n")
			else
			{
				printf("failure process => %d\n", statuscod);
				return (0);
			}
		}
	}
	return (1);
}

static int	process_child(t_lst *li, t_cmd node, int times)
{	
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
		exec_builtin(node.av, 1);
	else if (node.cmd && !ft_exec(&node))
	{
		msg_error("minishell: ", 0, node.av[0]); 
		ft_putstr_fd(": command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	exec_process(t_lst *li)
{
	int	status;	
	int	ret;
	int	pid[li->pipe + 1];
	int	times;
	
	if(li->pipe)
		init_pipe(li);
	//if (li->redir)
	init_redir(li->head, li);
	times = -1;
	while (++times <= li->pipe)
	{
		pid[times] = fork();
		if (pid[times] == -1)
			return (-1);
		else if (pid[times] == 0)
			process_child(li, *li->head, times);
		delete_first(&li);
	}
	close_fd(NULL, &li);
	unlink(".heredoc");
	return (process_daddy(&li));
}
