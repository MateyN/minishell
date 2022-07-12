#include "minishell.h"

/*
void	msg_error(char *s)
{
	perror(s);
}
*/

int	error_quote(char *s)
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
				return (TRUE);
			}
		}
		else if (*s == ';' || *s == '\\')
		{
			perror("Error caracter forbiden");
			return (TRUE);
		}
		s++;
	}
	return (FALSE);
}

int	error_redirection(char *s)
{
	char	c;
	
	c = s[ft_strlen(s) - 1];
	if (!redirection(c)) 
		return (FALSE);
	if (c == '|') //to do for pipe 
		return (FALSE);
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	return (TRUE);
		
}
