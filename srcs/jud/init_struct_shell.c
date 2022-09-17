/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_li_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:05:13 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/11 22:06:27 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//cette fonction dois verifier aussi les chaines qui ne sont pas dans les quotes

int	check_pipe(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (tab[++j])
		if (ft_strcmp(tab[j], "|") == 0)
	i++;
	return (i);
}

int	check_redir(t_lst **li)
{
	int	i;
	int	ret;
	char	**tab_temp;

	ret = 0;
	i = -1;
	(*li)->heredoc = 0;
	tab_temp = (*li)->tab;
	while(tab_temp[++i])
	{
		if (!ft_strncmp(tab_temp[i], "<<", 3))
		{
			(*li)->heredoc++;
			ret = TRUE;
		}
		if (!ft_strncmp(tab_temp[i], "<", 2) || \
		!ft_strncmp(tab_temp[i], ">", 2) || \
		!ft_strncmp(tab_temp[i], ">>", 3))
			ret = TRUE;
	}
	return (ret);
}

void	init_shell(t_lst *li, char **tab)
{
	int	i;

	li->tab = tab;
	tab = NULL;
	li->nb_arg = 0;
	i = -1;
	while (li->tab[++i])
		li->nb_arg++;
	li->pipe = check_pipe(li->tab);
	li->redirection = check_redir(&li);
	li->head = NULL;
	handle_action(&li);//parsing 	
	create_list(&li); //li->head init
}
