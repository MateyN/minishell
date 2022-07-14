/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:23:37 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/14 10:37:00 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_nval(char *key, char *str)
{
	int	i; // the start index of the substr in the str
	int	length;

	i = ft_strlen(key);
	length = ft_strlen(str);
	if (i + 1 == length)
		return (ft_strdup(""));
	else if (i + 1 > length)
		return (NULL);
	return (ft_substr(str, i + 1, length));
}

static char	*get_key(char *cmd, int start)
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

void	output_envp(void)
{
	int		i;
	char	*key;
	char	*val;

	i = -1;
	while (g_ms.env_p[++i])
	{
		key = get_key(g_ms.env_p[i], 0);
		val = get_environ(key);
		printf("declare -x ");
		printf("%s", key);
		if (ft_strchr(g_ms.env_p[i], '='))
			printf("=\"%s\"", val);
			printf("\n");
			free(key);
			key = NULL;
			free(val);
			val = NULL;
	}
	return ;
}