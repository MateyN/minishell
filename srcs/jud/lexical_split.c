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

int	double_dollar(char *s, int *i, int *ret)
{
	int	temp;
	
	temp = *i + 1;
	if (s[temp] == '$')
	{	
		while (s[temp] && (s[temp] != ' ' && s[temp] != '\"'))
		{
			(*ret)++;
			temp++;
		}
		*i = temp;
		return (1);
	}
	else
		return (0);
}

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
		while (s[i] && (s[i] != sep && s[i] != '|'))  
		{
			if (s[i] == '\'' || s[i] == '\"')
				exception(s, &i);
			++i;
			time = 1;
		}
		if (s[i] == '|')
			ret++;
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
	while (s[i] && (s[i] != sep && s[i] != '|'))
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
	while (s[*i] && (s[*i] != sep && s[*i] != '|')) 
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
	if (s[*i] == '|') //for copy | in tab
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
		if (s[i] == '|')
		{	
			tab[++j] = "|";	
			i++;
		}
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
