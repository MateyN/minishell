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
