/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:16:01 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:58:32 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)

{
	size_t			i;
	unsigned char	s;
	unsigned char	*mem;

	mem = b;
	s = c;
	i = 0;
	while (i < len)
	{
		mem[i] = s;
		i++;
	}
	return (b);
}
