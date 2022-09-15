/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:03:41 by mnikolov          #+#    #+#             */
/*   Updated: 2022/09/11 11:37:51 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	return (0);
}

void	exec_builtin(t_cmd *node, t_lst *ms)
{
	if (!ft_strncmp(node->cmd, "export\0", 7) && node->av[1])
		node->exit = ft_export(node->av[1], ms);
	else if (!ft_strncmp(node->cmd, "export\0", 7) && node->av[1] == NULL)
		sort_export(ms);
	else if (!ft_strncmp(node->cmd, "unset\0", 6) && node->av[1])
		ft_unset(node->av[1], ms);
	else if (!ft_strncmp(node->cmd, "echo\0", 5))
		ft_echo(node->av);
	else if (!ft_strncmp(node->cmd, "exit\0", 5))
		ft_exit(node->av, ms);
	else if (!ft_strncmp(node->cmd, "env\0", 4))
		ft_env(ms);
	else if (!ft_strncmp(node->cmd, "cd\0", 3))
		ft_cd(node->av[1], ms);
	else if (!ft_strncmp(node->cmd, "pwd\0", 4))
		pwd();
}
/*
int	parse_cmds(char *path, t_lst *ms)
{
	char	**args;

	if (!path)
		return (0);
	args = ft_split(path, ' ');
	if (check_builtin(args[0]))
		exec_builtin(args, path, ms);
	free_2ptr(args);
	return (0);
}*/
