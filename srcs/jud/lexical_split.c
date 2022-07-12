/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:30:03 by rmamison          #+#    #+#             */
/*   Updated: 2022/07/12 20:18:39 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exception(char *s, int *i, int flag)
{
	char	c;

	c = s[*i];
	if (flag == QUOTE)
		while (s[++(*i)] && s[*i] != c)
			;
	else if (flag == REDIR)
		while (s[++(*i)] && s[*i] == c)
			;
}

static	int	count_sep(char *s, char sep)
{
	int	ret;
	int	time;
	int	i;

	time = 0;
	ret = 0;
	i = -1;
	while (s[++i])
	{
		while (s[i] && (s[i] != sep && !redirection(s[i])))  
		{
			if (s[i] == '\'' || s[i] == '\"')
				exception(s, &i, QUOTE);
			++i;
			time = 1;
		}
		if (redirection(s[i]))
		{
			exception(s, &i, REDIR);
			ret++;
			--i;
		}
		if (time == 1)
			ret ++;
		time = 0;
	}
	return (ret);
}
/*-------------------------------------------*/

static int	len_word(char *s, char sep, int i)
{
	int	ret;
	char	quote;

	quote = ' ';
	ret = 0;
	if (redirection(s[i]) == 1)
		return (count_redirection(s, i));
	while (s[i] && (s[i] != sep && !redirection(s[i])))
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			ret++;
			while (s[++i] && s[i] != quote)
				ret++;
		}
		ret++;
		i++;
	}
	return (ret);
}
/*---------------------------------------------------*/

static char	*take_word(char *s, char sep, int *i)
{
	char	*word;
	char	quote;
	int	j;
	
	j = -1;
	word = malloc(sizeof(char) * (len_word(s, sep, *i) + 1));
	if (!word)
		return (NULL);
	if (redirection(s[*i]) == 1)
		write_redirection(&word, s, i);
	else
	{
		while (s[*i] && (s[*i] != sep && !redirection(s[*i]))) 
		{
			if (s[*i] == '\'' || s[*i] == '\"')
			{	
				quote = s[*i];
				word[++j] = s[*i];
				while (s[++(*i)] && s[*i] != quote)
					word[++j] = s[*i];
			}
			word[++j] = s[(*i)];
			++(*i);
		}
		word[++j] = '\0';
	}
	--(*i);
	return (word);
/* when the quote its not close I increment the index
for count the all char, my split must ignore the seperator 
in betwen the quote*/
}
/*-------------------------------------------------*/

char	**lex_split(char *s, char sep)
{
	char	**tab;
	int	i;
	int	j;
	
	if (!s)
		return (NULL);
	j = -1;
	i = -1;
	tab = (char **)malloc(sizeof(char *) * (count_sep(s, sep) + 1));
	if (!tab)
		return (NULL);
	while (++i <= (ft_strlen(s)))
	{	
		if (!s[i])
			break ;
		if (s[i] == sep)
			while (s[++i] == sep)
				;
		if (s[i] != sep && s[i])
			tab[++j] = take_word(s, sep, &i);
	}
	tab[j + 1] = NULL;
	j = -1;
	return (tab);
}
