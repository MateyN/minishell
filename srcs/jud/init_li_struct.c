#include "minishell.h"
//cette fonction dois verifier aussi les chaines qui ne sont pas dans les quotes
int     check_pipe(char **tab)
{
	int     i;
	int	j;
	
	i = 0;
	j = -1;
 	while (tab[++j])
		if (ft_strcmp(tab[j], "|") == 0)
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
