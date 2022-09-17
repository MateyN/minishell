/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_lexical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:11:10 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/11 21:53:23 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	home_sign(char **s, t_lst *li)
{
	char	*path_home;
	char	*temp_str;
	char	*temp;

	if ((*s)[0] == '~' && ((*s)[1] == '/' || !(*s)[1]))
	{
		temp_str = *s;
		path_home = get_env_value("HOME", li);
		temp = ft_strjoin(path_home, ++(temp_str));
		free(*s);
		*s = temp;
		temp = NULL;
	}
}

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
		else if (s[i] == '<') //PRIORI 2
			return (REDIR_IN);
		else if (s[i] == '>' && s[i + 1] == '>') //LAST 3
			return (REDIR_OUT_D);
		else if (s[i] == '>') //LAST 3
			return (REDIR_OUT_S);
	}
	return (FALSE);
}

void	handle_action(t_lst **li)
{
	int		i;
	int		flag;
	char	*temp;

	i = -1;
	temp = NULL;
	while ((*li)->tab[++i])
	{
		flag = quote_exist((*li)->tab[i]);
		home_sign(&(*li)->tab[i], *li);
		if (flag == S_QUOTE) // ('')
			temp = news_s_quote((*li)->tab[i]);
		else if (flag == D_QUOTE || flag == DOLLAR) //treat ("") & ("$") & ($)
			temp = news_d_quote((*li)->tab[i], *li);
		if (temp)
		{
			free((*li)->tab[i]);
			(*li)->tab[i] = temp;
			temp = NULL;
		}
	}
}
