/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:07:39 by mnikolov          #+#    #+#             */
/*   Updated: 2022/05/25 15:04:44 by mnikolov         ###   ########.fr       */
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
	(void)ac;
	(void)av;
	prompt_handle();
	g_ms.exit = 1;
	return (g_ms.exit);
}