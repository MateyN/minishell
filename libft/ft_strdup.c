/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:03:15 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/10 13:59:02 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)

{
	char	*str;
	int		i;
	int		lenght;

	str = (char *)s1;
	lenght = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (lenght + 1));
	if (str == NULL)
		return (0);
	i = 0;
	while (i < lenght)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
