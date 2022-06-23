/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:56:06 by mnikolov          #+#    #+#             */
/*   Updated: 2022/06/22 10:54:57 by mnikolov         ###   ########.fr       */
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
/*
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
    
}*/
