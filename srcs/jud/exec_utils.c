/* ************************************************************************** */

/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:07:39 by mnikolov          #+#    #+#             */
/*   Updated: 2022/07/21 18:45:44 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_fd(int fd_in, int fd_out)
{
	if (dup2(fd_in, fd_out) < 0)
		msg_error("error: dup2\n", 0, NULL);
}

void	close_fd(t_cmd *node, t_lst **li)
{
	int	i;

	i = -1;
	if (!(*li)->pipe)
		return ;
	while (++i < (*li)->pipe)
	{
		close((*li)->tube_fd[i][0]);
		close((*li)->tube_fd[i][1]);
	}
	if (node)
	{
		if (node->infile)
			close(node->infile);
		if (node->outfile)
			close(node->outfile);
	}
}

void	*take_path(char	***dest, char *cmd)
{
	char	**temp_env;
	char	*tmp_a;
	char	*tmp_b;
	int	i;	

	temp_env = g_ms.env_p;
	while (*temp_env && ft_strncmp(*temp_env, "PATH", 4))
		*(temp_env++);
	while (*temp_env && *(*temp_env)++ != '=')
		;
	*dest = ft_split(*temp_env, ':');
	i = -1;
	while ((*dest)[++i])
	{
		tmp_a = ft_strjoin((*dest)[i], "/");
		free((*dest)[i]);
		tmp_b = ft_strjoin(tmp_a, cmd);
		free(tmp_a);
		(*dest)[i] = tmp_b;
	}
}
