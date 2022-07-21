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

t_ms	g_ms;

void	print_list(t_lst *li)
{
	int	i;

	t_cmd *temp;

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
		temp = temp->next;
	}
	
}

void	getprompt(char **shell)
{
	*shell = readline(BOLDGREEN"Minishell$> "RESET);
	//return (*shell);
}

void	prompt_handle(void)
{
	t_lst	li;
	char	*shell;
	
	while (1)
	{
		getprompt(&shell);
		if (!error_exist(shell)) //quote/redir/;/(\)
		{
			init_struct(&li, lex_split(shell, ' '));
			handle_action(&li);
			take_tab(&li);
			if (check_builtin(li.head->cmd) == TRUE)
				exec_builtin(li.head->av, 1);
			free_all(&li);
		}
		free(shell);
	}
}

int	main(int ac, char **av, char **envp)
{
	//while (*envp)
	//	printf("%s\n",*envp++);
	(void)ac;
	(void)av;
	g_ms.env_p = envp; //to do//just for test
    	prompt_handle();
	g_ms.exit = 1;
	return (g_ms.exit);
}
