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
	t_redir *red;

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
		else{
		while (red)
		{
			printf("REDIR SIGN NAME:\n------\n%s\n", red->name);
			red = red->next;
		}}
		temp = temp->next;
	}
	
}

void	getprompt(char **shell)
{
	*shell = readline(BOLDGREEN"Minishell$> "RESET);
	//return (*shell);
}

/*void	prompt_handle(void)
{
	while (1)
	{
		getprompt(&shell);
		if (!error_exist(shell)) //quote/redir/;/(\)
		{
			init_struct(&li, lex_split(shell, ' '));
			handle_action(&li);
			take_tab(&li);
			//print_list(&li);
			if (!(id = exec_process(&li)))
				printf("error exec\n");//to_do save error id
			//print_list(&li);
			free_all(&li);
		}
		free(shell);
	//	if (li.head)
	//		print_list(&li);
	}
}
*/

int	main(int ac, char **av, char **envp)
{
	t_lst	li;
	char	*shell;
	int	id;
	(void)ac;
	(void)av;

	li.head = NULL;
	g_ms.env_p = envp; //to do//just for test
	while (1)
	{
		getprompt(&shell);
		if (!error_exist(shell)) //quote/redir/;/(\)
		{
			init_struct(&li, lex_split(shell, ' '));
			handle_action(&li);
			take_tab(&li);
			//print_list(&li);
			if (!(id = exec_process(&li)))
				printf("error exec\n");//to_do save error id
			//print_list(&li);
			free_all(&li);
		}
		free(shell);
	//	if (li.head)
	//		print_list(&li);
	}
	g_ms.exit = 1;
	return (g_ms.exit);
}
