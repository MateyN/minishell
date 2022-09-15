/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:07:39 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/12 19:33:54 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ms	g_ms;

void	print_list(t_lst *li)
{
	int		i;
	t_cmd	*temp;
	t_redir	*red;

	temp = li->head;
	if (!li->head)
	{
		printf("Empty list\n");
		return ;
	}
	while (temp && temp->av)
	{
		i = -1;
		printf("LIST:\n------\n");
		while (temp->av[++i])
			printf("%s\n", temp->av[i]);
		printf("------\n\n");
		i = -1;
		red = temp->redir;
		if (!red)
			printf("EMPTY =>> REDIR\n");
		else
		{
			while (red)
			{
				printf("REDIR SIGN NAME:\n------\n%s\n", red->name);
				red = red->next;
			}
			temp = temp->next;
		}
	}
}
/*if (!error_exist(shell)) //quote/redir/;/(\)
		{
			init_struct(&li, lex_split(shell, ' '));
			handle_action(&li);
			take_tab(&li);
			//print_list(&li);
			if (!(id = exec_process(&li)))
				;//to_do save error id
			//print_list(&li);
			free_all(&li);
		}
		free(shell);
	//	if (li.head)
	//		print_list(&li);
	}
}
*/
void	rl_replace_line(const char *text, int clear_undo);

int	exception_built(t_lst *li)
{	
	if (!ft_strncmp(li->head->cmd, "cd", 3) || \
	!ft_strncmp(li->head->cmd, "export", 7) || \
	!ft_strncmp(li->head->cmd, "unset", 6) || \
	!ft_strncmp(li->head->cmd, "exit", 5))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_lst	li;
	
	g_ms.exit = 0;
	li.env = NULL;
	update_env(envp, &li);
	while (1)
	{
		if (!get_line(&li))//ctrl + d if return is null
			break ;
		if (!error_exist(li.line))
		{
			init_shell(&li, lex_split(li.line, ' '));
			if (exception_built(&li) || \
			!li.pipe && check_builtin(li.head->cmd))
				exec_builtin(li.head, &li);
			else if (!exec_process(&li))
				;//to_do save error id
			free_all(&li);
			if (!li.line)
				break ;
			//if (&term.line)//need put line in t_lst for this
			//	break ;
		}
		tcsetattr(0, TCSANOW, &li.saved);
		free(li.line);
	}
	free_env(&li.env);
	write(1, "exit\n", 5);//ctrl + d
	return (0);
}
