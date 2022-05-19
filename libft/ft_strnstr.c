/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:49:20 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:59:38 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*haystack, const char *needle, size_t len)

{
	size_t	i;
	size_t	c;
	size_t	nlenght;
	char	*h;

	i = 0;
	h = (char *)haystack;
	nlenght = ft_strlen(needle);
	if (nlenght == 0 || h == needle)
		return (h);
	while (h[i] != '\0' && i < len)
	{
		c = 0;
		while (h[i + c] != '\0' && needle[c] != '\0'
			&& h[i + c] == needle[c] && i + c < len)
			c++;
		if (c == nlenght)
			return (h + i);
		i++;
	}
	return (0);
}
