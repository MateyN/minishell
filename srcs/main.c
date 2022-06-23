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

void	getprompt(char **shell)
{
	*shell = readline("Minishell$> ");
	//return (*shell);
}

void	prompt_handle(void)
{
	t_cmd	test;
	char	*shell;
	
	while (1)
	{
		getprompt(&shell);
		if ((check_quote(shell)) < 0)
		{
			free(shell);
			exit(EXIT_FAILURE);
		}
		test.av = lex_split(shell, ' ');
		if (!strncmp(test.av[0], "echo", 4))
			echo(&test);
		//while (*(test.av))
			//printf("%s\n", *(test.av++));
	}
}

int	main(int ac, char **av, char **envp)
{
	t_cmd c;

	//while (*envp)
	//	printf("%s\n",*envp++);
	(void)ac;
	(void)av;
    	prompt_handle();
	g_ms.exit = 1;
	return (g_ms.exit);
}
