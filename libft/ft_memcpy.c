/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:04:10 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:58:25 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)

{
	int		i;
	char	*d;
	char	*s;

	s = (char *)src;
	d = (char *)dest;
	if (dest == NULL && src == NULL)
	{
		return (NULL);
	}
	if (n == 0)
		return ((void *)dest);
	i = 0;
	while (n--)
	{
		d[i] = s[i];
		i++;
	}
	return ((void *)dest);
}
