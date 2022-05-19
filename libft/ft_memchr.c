/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:15:16 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:58:16 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)

{
	unsigned char	*chr;

	chr = (unsigned char *)s;
	while (n--)
	{
		if (*chr == (unsigned char)c)
			return ((void *)chr);
		chr++;
	}
	return (NULL);
}
