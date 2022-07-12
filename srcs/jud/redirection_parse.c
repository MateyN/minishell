/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:30:03 by rmamison          #+#    #+#             */
/*   Updated: 2022/07/12 20:18:32 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_redir(char	c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	write(2, &c, 1);
	ft_putstr_fd("\"\n", 2);
	exit (1);
}

int	redirection(char c)
{
	if (c != '|' && c != '>' && c != '<')
		return (0);
	return (1);
}

int	count_redirection(char *s, int i)//to do separer checkerror et count(check a mettre dans prompt tout au debut)
{
	int	redir;
	char	c;
	
	c = s[i];
	redir = 0;
	while (s[i] == c)
	{
		redir++;
		if (s[i + 1] == ' ')
		{
			while (s[++i] == ' ');
			if (redirection(s[i]))
				msg_redir(s[i]);
			--i;
		}
		else if (redir == 2 && c == '|')
			msg_redir(s[i]);
		else if (redir > 2)
			msg_redir(s[i]);
		i++;		
	}
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
