/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:30:03 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/24 12:19:25 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exception(char *s, int *i)
{
	char	quote;

	quote = s[*i];
	while (s[++(*i)] != quote)
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
		while (s[i] != sep && s[i])
		{
			if (s[i] == '\'' || s[i] == '\"')
				exception(s, &i);
			++i;
			time = 1;
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
	char	quote;
	int	ret;

	ret = 0;
	quote = ' ';
	while (s[i] && s[i] != sep)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			while (s[++i] && s[i] != quote)
				ret++;
			++i;
		}
		else
		{
			ret++;
			i++;
		}
	}
	return (ret);
}

static char	*take_word(char *s, char sep, int *i)
{
	char	quote;
	char	*word;
	int	j;
	
	j = -1;
	word = malloc(sizeof(char) * (len_word(s, sep, *i) + 1));
	if (!word)
		return (NULL);
	quote = ' ';
	while (s[*i] && s[*i] != sep)
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			quote = s[*i];
			while (s[++(*i)] && s[*i] != quote)
				word[++j] = s[*i];
			++(*i);
		}
		else
			word[++j] = s[(*i)++];
	}
	word[++j] = '\0';
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
	int	start;
	int	j;
	
	if (!s)
		return (NULL);
	j = -1;
	i = -1;
	start = -1;
	tab = (char **)malloc(sizeof(char *) * (count_sep(s, sep) + 1));
	if (!tab)
		return (NULL);
	while (++i <= (ft_strlen(s)))
	{	
		if (s[i] == sep)
			while (s[++i] == sep)
				;
		if (s[i] != sep && s[i])
			tab[++j] = take_word(s, sep, &i);
	}
	tab[j + 1] = NULL;
	return (tab);
}
