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

void	delete_first(t_lst *li)
{

	t_cmd *temp;	
	t_cmd *new;	

	new = NULL;
	temp = NULL;
	if (!li->head)
		return ;
	temp = li->head;
	while (temp != NULL)
	{
		new = temp->next;
		if (new)
			new->prev = NULL;
		free_tab(temp->av);
		temp->av = NULL;
		temp->cmd = NULL;
		free(li->head);
		li->head = new;
		temp = li->head;
	}
}

t_cmd	*get_node(char	**tab)
{
	t_cmd	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->av = tab;
	node->cmd = tab[0]; 
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	get_list(char **new_tab, t_lst **li)
{
	t_cmd 	*init;
	t_cmd	*temp;
	
	init = get_node(new_tab);
	if (!(*li)->head)
	{
		((*li)->head) = init;
		return ;
	}
	temp = ((*li)->head);
	while (temp && temp->next)
		temp = temp->next;
	init->prev = temp;
	temp->next = init;
}
/*-------------------------------*/

char	**sep_cmd(char **old, int *pos)
{
	int	i;
	char	**new;

	i = *pos;
	while (old[i] && old[i][0] != '|')
		i++;
	new = malloc(sizeof(char *) * ((i - *pos) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (old[*pos] && old[*pos][0] != '|')
		new[i++] = old[(*pos)++];
	new[i] = NULL;
	return (new);
}

void	take_tab(t_lst *li)
{
	int	i;
	int	pos;
	char	**new_tab;
	
	i = 0;
	pos = 0;
	new_tab = NULL;
	if (!li->tab)
		exit(1);
	else if (li->pipe > 0)
	{
		while (i++ <= li->pipe)
		{
			new_tab = sep_cmd(li->tab, &pos);
			get_list(new_tab, &li);
			new_tab = NULL;
			pos++;
		}
		free(li->tab);
		li->tab = NULL;
	}
	else
	{	
		new_tab = li->tab;
		get_list(new_tab, &li);
		new_tab = NULL;
	}
}
