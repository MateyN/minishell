/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:56:06 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/01 12:17:53 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *get_environ(char *key)
{
    int     i;
    char    *tmp;

    i = -1;
    if (ft_strlen(key) == 0)
        return (ft_strdup(""));
    if (!ft_strncmp(key, "?", ft_strlen(key)))
        return (ft_itoa(g_ms.exit));
    tmp = ft_strjoin(key, "=");
    while (g_ms.env_p[++i])
    {
        if (!ft_strncmp(tmp, g_ms.env_p[i], ft_strlen(tmp)))
            free(tmp);
            tmp = NULL;
            return (ft_substr(g_ms.env_p[i], ft_strlen(key), \
                ft_strlen(g_ms.env_p[i])));
    }
    free(tmp);
    tmp = NULL;
    return (ft_strdup(""));
}

char    *get_environ_key(char *cmd, int start)
{
    int     i;
    int     length;
    char    *key;

    length = 0;
    if (cmd[start] == '$')
        start++;
    i = start;
    if (cmd[i] == '?')
        return (ft_strdup(""));
    while (cmd[i])
    {
        if (!ft_isalnum(cmd[i]))
            break ;
            i++;
            length++;
    }
    key = ft_substr(cmd, start, length);
    return (key);
}

void    join_environ(char *key, char **tmp)
{
    char    *value;
    char    *tmp_parse;

    value = get_environ(key);
    tmp_parse = *tmp;
    *tmp = ft_strjoin(*tmp, value);
    free(value);
    value = NULL;
    free(tmp_parse);
    tmp_parse = NULL;
    return ;
}

void    cpy_environ(char **envp)
{
    int i;
    int length;

    i = -1;
    g_ms.env_p = (char **)malloc(sizeof(char *) * length + 1);
    if (!g_ms.env_p)
        return (ft_error());
    while (envp[++i])
        g_ms.env_p[i] = ft_strdup(envp[i]);
        g_ms.env_p[i] = NULL;
        return ;
}
