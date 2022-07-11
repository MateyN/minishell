#include "minishell.h"

int     check_pipe(char **tab)
{
	//pipe ne doit pas Ãtre a l'intÃrieur des quotes
	int     i;
	int	j;
	
	j = -1;
	i = 0;
 	while (tab[++j])
		if (tab[j][0] == '|')
			i++;
	return (i);
}

void 	init_struct(t_lst *li, char **tab)
{
	int	i;

	i = -1;
	li->tab = tab;
	li->nb_arg = 0;
	while (tab[++i])
		li->nb_arg++;
	li->pipe = check_pipe(li->tab);
	li->head = NULL;
	tab = NULL;
}
