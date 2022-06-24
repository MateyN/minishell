#include "minishell.h"

/*
void	msg_error(char *s)
{
	perror(s);
}
*/

int	check_quote(char *s)
{
	char	quote;
	
	quote = ' ';
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{	
			quote = *s;
			while (*(++s) != quote && *s)
				;
			if (*s == '\0')
			{
				perror("Error quote not close");
				return (-1);
			}
		}
		else if (*s == ';' || *s == '\\')
		{
			perror("Error caracter forbiden");
			return (-1);
		}
		s++;
	}
	return (0);
}
