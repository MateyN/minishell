#include "minishell.h"

int	quote_exist(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (FALSE);
	while (s[++i])
	{
		if (s[i] == '\'')
			return (S_QUOTE);
		else if (s[i] == '\"')
			return (D_QUOTE);
		else if (s[i] == '$')
			return (DOLLAR);
	}
	return (FALSE); 
}

int	redir_exist(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (FALSE);
	while (s[++i])
	{
		if (s[i] == '<' && s[i + 1] == '<') //PRIORI EXEC 1
			return (HEREDOC);
		else if (s[i] == '<') 		//PRIORI 2
			return (REDIR_IN);
		else if (s[i] == '>' && s[i + 1] == '>') //LAST 3
			return (REDIR_OUT_D);
		else if (s[i] == '>')			//LAST 3
			return (REDIR_OUT_S);
	}
	return (FALSE); 
}

void	handle_action(t_lst *li)
{
	int	i;
	int 	flag;
	char	*temp;

	i = -1;
	temp = NULL;
	while (li->tab[++i])
	{
		flag = quote_exist(li->tab[i]);
		if (flag  == S_QUOTE)// ('')
			temp = news_s_quote(li->tab[i]);
		else if (flag == D_QUOTE || flag == DOLLAR)//treat ("") & ("$") & ($)
			temp = news_d_quote(li->tab[i]);
		if (temp)
		{
			free(li->tab[i]);
			li->tab[i] = temp;
			temp = NULL;
		}
	}
	/*i = 0;
	while (li->tab[i])
		printf("tab=> %s\n", li->tab[i++]);*/
}


