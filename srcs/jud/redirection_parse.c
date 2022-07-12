/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:30:03 by rmamison          #+#    #+#             */
/*   Updated: 2022/07/11 19:16:56 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_redir(char	c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(&c, 2);
	ft_putstr_fd("\"\n", 2);
	exit (1);
}

int	redirection(char c)
{
	if (c != '|' && c != '>' && c != '<')
		return (0);
	return (1);
}

int	count_redirection(char *s, int i, int *times)
{
	int	redir;
	char	c;
	
	c = s[i];
	redir = 0;
	while (s[i] == c)
	{
		redir++;
		if (*times == 1)
			msg_redir(s[i]);
		else if (redir == 2 && c == '|')
			msg_redir(s[i]);
		else if (redir > 2)
			msg_redir(s[i]);
		i++;		
	}
	*times = 1;
	return (redir);
}

void	write_redirection(char **p_word, char *s, int *i)
{
	int	j;
	char	c;

	j = 0;
	c = s[*i];
	while (s[*i] && s[*i] == c)
		(*p_word)[j++] = s[(*i)++];
	(*p_word)[j] = '\0'; 
}
