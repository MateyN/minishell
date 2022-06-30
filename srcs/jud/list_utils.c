#include "minishell.h"

int	check_pipe(t_lst *li, char **tab)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (*(tab))
	{
		if (*(tab) == "|")
			li->pipe++;
		*(tab++);
	}
	return (li->pipe);
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
}

void	get_list(t_lst *li, char **tab)
{
	t_cmd *init;
	t_cmd	*temp;

	init = get_node(s);
	if (!li->head)
	{
		li->head = init;
		return ;
	}
	temp = li->head;
	while (temp->next != NULL)
		temp = temp->next;
	init->prev = temp;
	temp->next = init;
}

void	take_tab(t_lst *li, char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		exit(1);
	if (check_pipe(li, tab))
	{
		while (++i <= pipe)
		{
			new_tab = <-tab[i];
			get_list(li, new_tab)
			free_tab(new_tab);
		}
	}
	else
		get_list(li, tab);
}
