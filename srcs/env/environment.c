/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:56:06 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/30 10:52:48 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//char    *get_environ()
//{
//
//}

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

int check_env_key(char *key)
{
    int i;

    i = 0;
    if (!ft_isalpha(key[i]) && key[i] != '_')
        return (FALSE);
    else
        i++;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
        return (FALSE);
        i++;
    }
    return (TRUE);
}

int get_index(char *key)
{
    int     i;
    char    **tmp;

    i = -1;
    while (g_ms.env_p[++i])
    {
        tmp = ft_split(g_ms.env_p[i], '=');
        if (!ft_strncmp(tmp[0], key, ft_strlen(key) + 1))
        {
            free(tmp);
            return (i);
        }
        free(tmp);
    }
    return (1);
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
