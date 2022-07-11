#include "minishell.h"

static int      len_var(char    *s, int i)
{
	int     ret;

	ret = 0;
	while ((s[++i]) && (s[i] != '\"' && s[i] != ' ') \
			&& (s[i] != '$' && s[i] != '\''))
		ret++;
	return (ret);
}
/*-----------------------------------*/

static char *news_s_quote(char *s)
{	
	int	i;
	int	j;
	int	quote;
	char	*temp;

	i = -1;
	quote = 0;
	while (s[++i])
		if (s[i] == '\'')
			quote++;
	temp = malloc(sizeof(char) * ((i - quote) + 1));
	if (!temp)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] != '\'')
			temp[j++] = s[i];
	temp[j] = '\0';
	return (temp);		
}
/*-----------------------------------*/

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
		if (s[i] != '\"' && s[i] != '$')
			car++;
		if (s[i] != '$')
			i++;
	}
	int a = car + dollar;
	return (car + dollar);	
}
/*-----------------------------------*/

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
/*-----------------------------------*/

static int	recheck_cmp(char *env, char *temp)
{
	int	i;
	
	i = -1;
	while (env[++i] && env[i] != '=')
		;
	if (ft_strncmp(env, temp, i) == 0)
		return (TRUE);
	else 
		return (FALSE);
}
	/*-------------------*/

char	*handle_sign(char *s, int *i)
{
	char	*temp;
	int	j;
	int	size;
	
	temp = malloc(sizeof(char) * (len_var(s, *i) + 1));
	if (!temp)
		return (NULL);
	j = -1;
	while ((s[++(*i)]) && (s[*(i)] != ' ' && s[*(i)] != '\"') \
			&& (s[*i] != '$' && s[*i] != '\''))
		temp[++j] = s[(*i)];
	temp[++j] = '\0';
	size = j; 
	j = -1;
	while (g_ms.env_p[++j])
	{	
		if(ft_strncmp(temp, g_ms.env_p[j], size) == 0 \
				&& (recheck_cmp(g_ms.env_p[j], temp) == TRUE)) //need it for check the exact size to env before '='
		{
			free(temp);
			return (take_val_var(g_ms.env_p[j]));
		}
	}
	free(temp);
	return (NULL);
}
/*-----------------------------------*/


static char	*news_d_quote(char *s)
{
	int	i;
	int	j;
	char	*temp;
	char	*env_val;
	int a;
	
	temp = malloc(sizeof(char) * (len_d_quote(s) + 1));
	if (!temp)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			env_val = handle_sign(s, &i);
			if (env_val)
			{
				a = -1;
				while (env_val[++a])
					temp[j++] = env_val[a];
				free(env_val);
			}
		}
		if (s[i] && (s[i] != '\"' && s[i] != '$'))//need improvement
			temp[j++] = s[i];
		if (s[i] != '$')
			i++;
	}
	temp[j] = '\0';
	return (temp);
}

static int	test_s_quote(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'')
			return (1);
		else if (s[i] == '\"' || s[i] == '$')
			return (2);
	}
	return (FALSE); 
}

void	handle_action(t_lst *li)
{
	int	i;
	char *temp;

	i = -1;
	temp = NULL;
	while (li->tab[++i])
	{
		if (test_s_quote(li->tab[i]) == 1)
			temp = news_s_quote(li->tab[i]);
		else if (test_s_quote(li->tab[i]) == 2) 
			temp = news_d_quote(li->tab[i]);
		if (temp)
		{
			free(li->tab[i]);
			li->tab[i] = temp;
			temp = NULL;
		}
	}
	
}
