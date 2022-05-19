/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:39:04 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:58:55 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count(char const *s, char c)
{
	size_t	ret;
	size_t	i;

	ret = 0;
	i = 0;
	while (s[i])
	{
		if ((!s[i + 1] || s[i + 1] == c) && s[i] != c)
			ret++;
		i++;
	}
	return (ret + 1);
}

char	**ft_free(char **s, size_t i)
{
	while (i--)
		free(s[i]);
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**ret;
	size_t	i;

	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * ft_count(s, c));
	if (!ret)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len)
			ret[i] = ft_substr(s, 0, len);
		if (len && !ret[i++])
			return (ft_free(ret, i));
		s += len;
	}
	ret[i] = NULL;
	return (ret);
}
