#include "minishell.h"
/*
static int	token_exist(char *s);

void	push_tab(char **tab, char *data)
{
	int	i;

	i = -1;
}

void	redim_tab(t_lst **li, int token, char **dest, int *pos)
{
	int	time;
	int	before;
	char	*temp;

	time = *pos;
	temp = (*li)->tab[time];
	*dest = (*li)->tab[time + 1];
	//free(temp);
	before = time + 2;
	if((*li)->tab[before])
	{	
		while ((*li)->tab[before])
		{
			(*li)->tab[time++] = (*li)->tab[before];
			(*li)->tab[before++] = NULL;
		}
	}
	else 
	{
		(*li)->tab[time] = NULL;
		(*li)->tab[time + 1] = NULL;

	}
	--*pos;
}

int	count_limiter(char **tab, int i, int token)
{
	int	ret;

	ret = 0;
	while (tab[i] && tab[i][0] != '|')
	{
		if (token_exist(tab[i]) == token)
			ret++;
		i++;
	}
	return (ret);	
}

void	take_limiter(t_lst **li, int *pos, int	token)
{
	int	i;
	int	j;
	int	nb_lim;
	char	**redir;

	i = 0;
	j = *pos;
	nb_lim = count_limiter((*li)->tab, *pos, token);
	redir = malloc(sizeof(char *) * (nb_lim + 1));
	if (!redir)
		msg_error("malloc: error: **limiter", 0, NULL);
	if (nb_lim > 1)
	{
		while ((*li)->tab[j])
			if (token_exist((*li)->tab[j]) == token)
				redim_tab(li, token, &(redir[i++]), &j);
	}	
	else
	{
		redim_tab(li, token, &(redir[i++]), &j);
	}
	redir[i] = NULL;
	if (token == HEREDOC)
		(*li)->redir->limiter = redir;
	else if (token == REDIR_OUT_S || token == REDIR_OUT_D)
		(*li)->redir->outfile = redir;
	--(*pos);
}*/

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
}


