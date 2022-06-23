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

char	*getprompt(char **shell)
{
	*shell = readline("Minishell$> ");
	return (*shell);
}

void	prompt_handle(void)
{
	char	*shell;
	getprompt(&shell);
}

int	main(int ac, char **av, char **envp)
{
	while (*envp)
		printf("%s\n",*envp++);
	(void)ac;
	(void)av;
    	prompt_handle();
	g_ms.exit = 1;
	return (g_ms.exit);
}
