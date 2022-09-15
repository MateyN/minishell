/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:15:36 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/11 22:18:36 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	check_pipe(t_lst *li)
{
	int	i;
	int	j;
	char	**temp;

	temp = li->tab;
	i = -1;
	j = -1;
	while (*temp)
	{
		if ((**temp) == '|')
			li->pipe++;
		(*temp)++;
	}
	return (li->pipe);
}*/
/*--------------------------------*/
static void	delete_redir(t_redir *node)
{
	t_redir	*temp;	
	t_redir	*old;	

	old = NULL;
	temp = NULL;
	if (!node)
		return ;
	temp = node;
	while (temp != NULL)
	{
		old = temp;
		temp = temp->next;
		free(old);
		old = NULL;
	}
}

void	delete_first(t_lst **li)
{
	t_cmd	*temp;	
	t_cmd	*new;	

	new = NULL;
	temp = NULL;
	if (!(*li)->head)
		return ;
	temp = (*li)->head;
	if (temp != NULL)
	{
		new = temp->next;
		if (new)
			new->prev = NULL;
		if (temp->redir)
			delete_redir(temp->redir);
		free(temp->av);
		temp->av = NULL;
		temp->cmd = NULL;
		free((*li)->head);
		(*li)->head = new;
	}
}

static void	take_redir(char *s, int flag, t_cmd **cmd_node)
{
	t_redir	*node_redir;
	t_redir	*temp;

	node_redir = malloc(sizeof(*node_redir));
	if (!node_redir)
		return ;
	node_redir->name = s;
	node_redir->sign = flag;
	node_redir->next = NULL;
	if (!(*cmd_node)->redir)
	{
		node_redir->pos = 1;
		(*cmd_node)->redir = node_redir;
		return ;
	}	
	temp = (*cmd_node)->redir;
	while (temp && temp->next)
		temp = temp->next;
	node_redir->pos = temp->pos + 1;
	temp->next = node_redir;
}
/*----------------------------------*/

static char	**take_argv(char **tab, int *pos, t_cmd *node)
{
	int		i;
	int		count;
	int		flag;
	char	**new;

	i = *pos;
	count = 0;
	flag = 0;
	while (tab[i] && ft_strcmp(tab[i], "|") != 0)
	{
		flag = redir_exist(tab[i]);
		if (flag)
		{
			take_redir(tab[i + 1], flag, &node);
			count += 2;
		}
		i++;
	}
	new = malloc(sizeof(char *) * (((i - *pos) - count) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (tab[*pos] && ft_strcmp(tab[*pos], "|") != 0)
	{
		if (redir_exist(tab[*pos]) == HEREDOC && !tab[*pos + 1])
			break ;
		if (redir_exist(tab[*pos]))
				(*pos) += 2;
		else
			new[i++] = tab[(*pos)++];
	}
	new[i] = NULL;
	return (new);
}
/*--------------------------------*/

static void	get_list(t_lst **li, int *pos)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = malloc(sizeof(*node));
	if (!node)
		return ;
	node->redir = NULL;
	node->av = take_argv((*li)->tab, pos, node);
	node->cmd = node->av[0];
	node->infile = 0;
	node->outfile = 0;
	node->fd_file = 0;
	node->next = NULL;
	if (!(*li)->head)
	{
		node->prev = NULL;
		((*li)->head) = node;
		return ;
	}
	temp = (*li)->head;
	while (temp && temp->next)
		temp = temp->next;
	node->prev = temp;
	temp->next = node;
}
/*-------------------------------*/

void	create_list(t_lst **li)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	if (!(*li)->tab)
		exit(1);
	while (i++ <= (*li)->pipe)
	{
		get_list(li, &pos);
		pos++;
	}
}
