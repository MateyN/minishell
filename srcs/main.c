/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:07:39 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/30 16:35:50 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ms	g_ms;

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
		if ((check_quote(shell)) < 0)
		{
			free(shell);
			exit(EXIT_FAILURE);
		}
		init_struct(&li, lex_split(shell, ' '));
		handle_action(&li);
		if (check_builtin(li.tab[0]) == TRUE)
			exec_builtin(&li, 1);
		//while (*(li.tab))
		//	printf(" from main ::> %s\n", *(li.tab++));
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
