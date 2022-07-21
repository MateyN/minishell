#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab == NULL)
		return;
	while (tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}

void	free_list(t_lst *li)
{
	while (li->head)
		delete_first(li);
}

void	free_all(t_lst *li)
{
	free_tab(li->tab);
	li->tab = NULL;
	free_list(li);
}
