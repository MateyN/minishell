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
	*shell = readline(BOLDGREEN"Minishell$> "RESET);
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
		test.cmd = test.av[0];
		if (check_builtin(test.cmd) == TRUE)
			exec_builtin(&test, 1);
		//while (*(test.av))
			//printf("%s\n", *(test.av++));
	}
}

int	main(int ac, char **av, char **envp)
{
	//while (*envp)
	//	printf("%s\n",*envp++);
	(void)ac;
	(void)av;
    cpy_environ(envp);
    	prompt_handle();
	g_ms.exit = 1;
	return (g_ms.exit);
}
