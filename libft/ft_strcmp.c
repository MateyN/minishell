#include <stdio.h>
#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	str1;
	unsigned char	str2;
	if (!s1 || *s2 == ' ')
		return (-1);
	while (1)
	{
		str1 = (unsigned char) *s1++;
		str2 = (unsigned char) *s2++;
		if (str1 == '\0' && str2 == '\n')
			return (0);
		if (str1 != str2)
			return(str1 - str2);
	}
	return (0);
}
