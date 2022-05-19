/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:52:07 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/16 13:54:43 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int nbr)

{
	int	len;

	if (nbr <= 0)
		len = 1;
	else
		len = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

int	ft_pos_help(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*res;

	if (n < 0)
		sign = -1;
	else
		sign = 1;
	len = ft_len(n);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (0);
	res[len] = '\0';
	len--;
	while (len >= 0)
	{
		res[len] = '0' + ft_pos_help(n % 10);
		n = ft_pos_help(n / 10);
		len--;
	}
	if (sign == -1)
		*res = '-';
	return (res);
}
