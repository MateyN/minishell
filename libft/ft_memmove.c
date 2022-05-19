/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:49:11 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:58:29 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)

{
	char	*dest;
	char	*source;

	dest = (char *)dst;
	source = (char *)src;
	if (!len)
		return (dest);
	if (dest <= source)
		return (ft_memcpy(dest, source, len));
	source = source + len;
	dest = dest + len;
	while (len--)
		*--dest = *--source;
	return (dest);
}
