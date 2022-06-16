/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:06 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/15 17:01:20 by mnikolov         ###   ########.fr       */
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

	new_tmp = ft_strjoin("=", new_val);
	tmp = (char **)malloc(sizeof(char *) * (length + 1));
	if (!tmp)
		return (ft_error());
	i = -1;
	while (g_ms.env_p[++i])
		tmp[i] = g_ms.env_p[i];
	if (new_tmp != NULL)
		tmp[i++] = ft_strjoin(key, new_val);
	else
		tmp[i++] = ft_strdup(key);
	tmp[i] = NULL;
	free (g_ms.env_p);
	g_ms.env_p = tmp;
	free (new_tmp);
	new_tmp = NULL;
	return ;
}

void	export_error(char *av)
{
	ft_putstr_fd("MINISHELL: export: ", STDERR_FILENO);
	ft_putstr_fd(av, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	g_ms.exit = 1;
	return ;
}

void	export()
{
	
}
