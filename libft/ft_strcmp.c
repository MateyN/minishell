/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:17:20 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:59:34 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	str1;
	unsigned char	str2;

	while (1)
	{
		str1 = (unsigned char) *s1++;
		str2 = (unsigned char) *s2++;
		if (str1 != str2)
			return (str1 - str2);
		if (str1 == '\0')
			return (0);
	}
	return (0);
}
