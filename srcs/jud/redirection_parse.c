/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:19:02 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/11 22:20:14 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection(char c)
{
	if (c != '|' && c != '>' && c != '<')
		return (0);
	return (1);
}

int	count_redirection(char *s, int i) //to do separer checkerror et count(check a mettre dans prompt tout au debut)
{
	int		redir;
	char	c;

	c = s[i];
	redir = 0;
	while (s[i] == c)
	{
		redir++;
		i++;
	}
	return (redir);
}

void	write_redirection(char **p_word, char *s, int *i)
{
	int		j;
	char	c;

	j = 0;
	c = s[*i];
	while (s[*i] && s[*i] == c)
		(*p_word)[j++] = s[(*i)++];
	(*p_word)[j] = '\0';
}