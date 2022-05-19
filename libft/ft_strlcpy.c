/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:05:48 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:59:16 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)

{
	size_t	i;
	char	*dest;
	char	*s;

	dest = (char *)dst;
	s = (char *)src;
	if (dstsize > 0)
	{
		i = 0;
		while (i < dstsize - 1)
		{
			if (s[i] == '\0')
				break ;
			dest[i] = s[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(s));
}
