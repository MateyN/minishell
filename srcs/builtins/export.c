/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:06 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/14 11:53:58 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//void	export(t_cmd *command);

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

void	set_new_env(char *new_val, char *key)
{
	int		i;
	int		length;
	char	**tmp;
	char	*new_tmp;

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

static void	export_error(char *av)
{
	ft_putstr_fd("MINISHELL: export: `", STDERR_FILENO);
	ft_putstr_fd(av, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	g_ms.exit = 1;
	return ;
}

static void	handle_export(char *av)
{
	char	*key;
	char	*new_val;

	key = get_environ_key(av, 0);
	new_val = get_nval(key, av);
	if (!check_env_key(key))
		return (export_error(av));
	if (get_index(key) >= 0)
			update_environ(key, new_val);
	else
		set_new_env(key, new_val);
		free(key);
		key = NULL;
		free(new_val);
		new_val = NULL;
}

void	export(t_cmd *command)
{
	int i;

	g_ms.exit = 0;
	if (command->ac == 1)
		return (output_envp());
	i = 0;
	while (command->av[++i])
		handle_export(command->av[i]);
}

