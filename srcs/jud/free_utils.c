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
/*
void	free_pipe_fd(t_lst *li)
{
	int	i;
	int	j;

	if (!li->pipe)
		return ;
	i = li->pipe * 2;
	j = 0;
	while (i--)
		free(li->tube_fd[j++]);
}*/

void	free_all(t_lst *li)
{
	free_tab(li->tab);
	li->tab = NULL;
	if (li->pipe)
		free(li->tube_fd);
	free_list(li);
}
