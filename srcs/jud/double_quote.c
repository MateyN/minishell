#include "minishell.h"
static int      len_var(char    *s, int i)
{
	int     ret;

	ret = 0;
	while ((s[++i]) && (s[i] != '\"' && s[i] != ' '))
		ret++;
	return (ret);
}

static int	len_s_quote(char *s)
{	
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (s[++i])
		if (s[i] == '\'')
			quote++;
	return (i - quote);		
}

int	len_d_quote(char *s)
{
	int	i;
	int	quote;
	int	dollar;
	int	car;
	char	*temp;

	i = 0;
	dollar = 0;
	car = 0;
	temp = NULL; 
	while (s[i])
	{
		if(s[i] == '$')
		{	
			temp =  handle_sign(s, &i);
			if (temp)
			{	
				dollar += (int)ft_strlen(temp);
				free(temp);
			}
		}
		if (s[i] != '\"')
			car++;
		i++;
	}
	return (car + dollar);	
}

char	*take_val_var(char *s)
{
	int	i;
	int	j;
	char	*temp;

	i = -1;
	while (s[++i] && s[i] != '=')
		;
	++i;
	j = i;
	while (s[i])
		i++;
	temp = malloc(sizeof(char) * (i - j + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (s[j])
		temp[++i] = s[j++];
	temp[++i] = '\0';
	return (temp);
}

char	*handle_sign(char *s, int *i)
{
	char	*temp;
	int	j;
	int	size;
	
	temp = malloc(sizeof(char) * (len_var(s, *i) + 1));
	if (!temp)
		return (NULL);
	j = -1;
	while ((s[++(*i)]) && (s[*(i)] != ' ' && s[*(i)] != '\"'))
		temp[++j] = s[(*i)];
	temp[++j] = '\0';
	printf("%s\n", temp);
	size = j; 
	j = -1;
	while (g_ms.env_p[++j])
	{	
		if(ft_strncmp(g_ms.env_p[j], temp, size) == 0)
		{
			free(temp);
			temp = NULL;
			return (take_val_var(g_ms.env_p[j]));
		}
	}
	free(temp);
	return (NULL);
}
/*
void	single_quote(char **s)
{
	char	*temp

	temp = malloc(sizeof(char) * (len_s_quote(s) + 1));
	while (s[(*i)] && s[(*i)] != '\"')
	{	
		if (s[(*i)] == '$' && s[*i + 1] != '$')
		{
			temp = handle_sign(s, i);
			while (*temp)
				(*tab)[++(*j)] = *(temp++);
			//free(temp);
			temp = NULL;
		}
		else if (s[(*i)] == '$' && s[*i + 1] == '$')
			while (s[++(*i)] != ' ' && s[(*i)] != '\"')
				(*tab)[++(*j)] = s[(*i)];
		else
			(*tab)[++(*j)] = s[(*i)++];
	}
}

void	double_quote(char **tab, int *j, char *s, int *i)
{
	char	*temp;

	temp = NULL;
	++(*i);
	while (s[(*i)] && s[(*i)] != '\"')
	{	
		if (s[(*i)] == '$' && s[*i + 1] != '$')
		{
			temp = handle_sign(s, i);
			while (*temp)
				(*tab)[++(*j)] = *(temp++);
			//free(temp);
			temp = NULL;
		}
		else if (s[(*i)] == '$' && s[*i + 1] == '$')
			while (s[++(*i)] != ' ' && s[(*i)] != '\"')
				(*tab)[++(*j)] = s[(*i)];
		else
			(*tab)[++(*j)] = s[(*i)++];
	}
}*/
