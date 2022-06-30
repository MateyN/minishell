/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:07:39 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/16 15:09:17 by mnikolov         ###   ########.fr       */
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
		printf("len av 2m %d\n", len_d_quote(li.tab[1]));
		//if (check_builtin(test.cmd) == TRUE)
			//exec_builtin(&test, 1);
		while (*(li.tab))
			printf("%s\n", *(li.tab++));
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
