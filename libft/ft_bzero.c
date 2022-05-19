/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:14:16 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:56:35 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)

{
	size_t			i;
	unsigned char	*mem;
	unsigned char	b;

	mem = s;
	b = '\0';
	i = 0;
	while (i < n)
	{
		mem[i] = b;
		i++;
	}
}
