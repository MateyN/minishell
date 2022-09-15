/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quote_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:20:34 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/12 10:12:06 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_sign(char *s, int *i, t_lst *li);

static int	len_var(char *s, int i)
{
	int	ret;

	ret = 0;
	while ((s[++i]) && (s[i] != '\"' && s[i] != ' ') \
			&& (s[i] != '$' && s[i] != '\''))
		ret++;
	return (ret);
}
/*-----------------------------------*/

static int	len_d_quote(char *s, t_lst *li)
{
	int		i;
	int		quote;
	int		dollar;
	int		car;
	char	*temp;

	i = 0;
	dollar = 0;
	car = 0;
	temp = NULL;
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1] != ' ' && s[i + 1]))
		{	
			temp = handle_sign(s, &i, li);
			if (temp)
			{	
				dollar += (int)ft_strlen(temp);
				free(temp);
			}
		}
		else if (s[i] != '\"')
			car++;
		if (s[i] != '$' || s[i] == '$' && (s[i + 1] == ' ' || !s[i + 1]))
			i++;
	}
	return (car + dollar);
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

static char	*take_val_var(char *s)
{
	int		i;
	int		j;
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

static char	*handle_sign(char *s, int *i, t_lst *li)
{
	char	*temp;
	char	*ret;
	int		j;

	temp = malloc(sizeof(char) * (len_var(s, *i) + 1));
	if (!temp)
		return (NULL);
	j = -1;
	while ((s[++(*i)]) && (s[*(i)] != ' ' && s[*(i)] != '\"') \
			&& (s[*i] != '$' && s[*i] != '\''))
		temp[++j] = s[(*i)];
	temp[++j] = '\0'; //take name var ($NAME_VAR)
	if (!temp[1] && temp[0] == '?')
		ret = ft_itoa(g_ms.exit);
	else 
		ret = ft_strdup(get_env_value(temp, li));
	free(temp);
	return (ret);
}

char	*news_s_quote(char *s)
{	
	int		i;
	int		j;
	int		quote;
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

char	*news_d_quote(char *s, t_lst *li)
{
	int		i;
	int		j;
	int		a;
	char	*temp;
	char	*env_val;

	temp = malloc(sizeof(char) * i + 1);
	if (!temp)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == '$' && (s[i + 1] != ' ' && s[i + 1] != '\"'\
			&& s[i + 1] != '\'' && s[i + 1]))
		{
			env_val = handle_sign(s, &i, li);
			if (env_val)
			{
				a = -1;
				while (env_val[++a])
					temp[j++] = env_val[a];
				free(env_val);
			}
			--i;
		}
		else if (s[i] && s[i] != '\"') //need improvement
			temp[j++] = s[i];
		//if (s[i] != '$' || s[i] == '$' && (s[i + 1] == ' ' || !s[i + 1]))
	}
	temp[j] = '\0';
	return (temp);
}
