/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:23:37 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/07 11:57:51 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key(char *cmd, int start)
{
	int		i;
	int		length;
	char	*key;

	length = 0;
	if (cmd[start] == '$')
		start++;
	i = start;
	while (cmd[i])
	{
		if (cmd[i] == '/' || cmd[i] == '$' || cmd[i] == '"' \
			|| cmd[i] == ' ' || cmd[i] == '.' || cmd[i] == '=' \
			|| cmd[i] == '|')
			break ;
		i++;
		length++;
	}
	key = ft_substr(cmd, start, length);
	return (key);
}

char	*get_nval(char *key, char *str)
{
	int	i; // the start index of the substr in the str
	int	length;

	i = ft_strlen(key);
	length = ft_strlen(str);
	if (i == length)
		return (ft_strdup(""));
	else if (i > length)
		return (NULL);
	return (ft_substr(str, i, length));
}

void	set_new_env(char *new_val, char *key)
{
	int		i;
	int		length;
	char	**tmp;
	char	*new_tmp;

	//length = 0;
	new_tmp = ft_strjoin("=", new_val);
	length = len_2ptr(g_ms.env_p);
	tmp = (char **)malloc(sizeof(char *) * (length + 2));
	if (!tmp)
		return (ft_error());
	i = -1;
	while (g_ms.env_p[++i])
		tmp[i] = g_ms.env_p[i];
	if (new_tmp != NULL)
		tmp[i++] = ft_strjoin(key, new_tmp);
	else
		tmp[i++] = ft_strdup(key);
	tmp[i] = NULL;
	free (g_ms.env_p);
	g_ms.env_p = tmp;
	free (new_tmp);
	new_tmp = NULL;
	return ;
}

void	update_environ(char *key, char *new_val)
{
	int		i;
	char	*new_environ_val;
	char	*new_tmp;

	new_tmp = ft_strjoin("=", new_val);
	i = get_index(key);
	free(g_ms.env_p[i]);
	g_ms.env_p[i] = NULL;
	if (new_tmp != NULL)
		new_environ_val = ft_strjoin(key, new_tmp);
	else
		new_environ_val = ft_strdup(key);
		g_ms.env_p[i] = new_environ_val;
		free(new_tmp);
		new_tmp = NULL;
		return ;
}