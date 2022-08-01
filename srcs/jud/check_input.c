#include "minishell.h"

void	msg_error(char *s1, char c, char *s2)
{
	ft_putstr_fd(s1, 2);
	if (c)
		write(2, &c, 1);
	if (s2)
		ft_putstr_fd(s2, 2);
}

static int	error_quote(char *s, int *i)
{
	char	quote;
	
	quote = s[*i];
	while (s[++(*i)] && s[*i] != quote)
		;
	if (s[*i] == '\0')
	{
				msg_error("minishell: Error quote not close\n", 0, NULL);
				return (TRUE);
	}
	return (FALSE);
}

static int	error_redirection(char *s, int *i)
{
	char	c;
	char	error;
	int 	redir;

	error = 0;
	redir = 0;
	c = s[*i];
	while (s[*i] == c)
	{
		++redir;
		if (redirection(s[*i + 1]) && s[*i + 1] != s[*i] && c != '|')
			error = s[*i + 1];
		else if (s[*i + 1] == ' ')
		{
			while (s[++(*i)] && s[*i] == ' ')
				;
			if (redirection(s[*i]) && c != '|')
				error = s[*i];
		}
		else if (redir > 2 || (redir == 2 && c == '|'))
			error = s[*i];
		else if (redir == 2 && c == '<' && !s[*i])
			break ;
		if (error)
		{
			msg_error("minishel: syntax error near unexpected token `", error, "\"\n");
			return (TRUE);
		}
		++(*i);
	}
	--(*i);
	return (FALSE);
}

int	error_exist(char *s)
{	
	int		i;

	if (redirection(s[ft_strlen(s) - 1]) && s[ft_strlen(s) - 2] != '<')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (TRUE);
	}
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (error_quote(s, &i))
				return (TRUE);
		}
		else if (redirection(s[i]))
		{
			if (error_redirection(s, &i))
				return (TRUE);
		}
		else if (s[i] == ';' || s[i] == '\\')
		{
			msg_error("minishell: Error caracter forbiden\n", 0, NULL);
			return (TRUE);
		}
	}
	return (FALSE);
}
