/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:37:27 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:59:13 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)

{
	char	*d;
	char	*s;
	size_t	n;
	size_t	d_lenght;

	d = (char *)dst;
	s = (char *)src;
	n = dstsize;
	while (n-- != 0 && *d != '\0')
		d++;
	d_lenght = d - dst;
	n = dstsize - d_lenght;
	if (n == 0)
		return (d_lenght + ft_strlen(s));
	while (*s != '\0')
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (d_lenght + (s - src));
}
