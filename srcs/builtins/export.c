/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:10:06 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/01 12:25:15 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export(t_cmd *command);

void	export_error(char *av)
{
	ft_putstr_fd("MINISHELL: export: ", STDERR_FILENO);
	ft_putstr_fd(av, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	g_ms.exit = 1;
	return ;
}

void	handle_export(char *av)
{
	char	*key;
	char	*new_val;

	key = get_environ_key(av, 0);
	new_val = get_nval(key, av);
	if (!check_env_key(key))
		return (export_error(av));
	if (key >= 0)
			set_new_env(key, new_val);
		free(key);
		key = NULL;
		free(new_val);
		new_val = NULL;
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

