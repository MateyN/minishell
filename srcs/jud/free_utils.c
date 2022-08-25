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
		delete_first(&li);
}

void	free_pipe(t_lst *li)
{
	int	i;

	if (!li->pipe)
		return ;
	i = -1;
	while (++i < li->pipe)
		free(li->tube_fd[i]);
	free(li->tube_fd);
}

void	free_all(t_lst *li)
{
	free_tab(li->tab);
	li->tab = NULL;
	if (li->pipe)
		free_pipe(li);
	free_list(li);
}
