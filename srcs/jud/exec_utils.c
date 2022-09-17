/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:54:21 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/17 17:08:32 by rmamison         ###   ########.fr       */
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

void	take_path(char	***dest, char *cmd, t_lst *li)
{
	char	*tmp_a;
	char	*tmp_b;
	int		i;	

	*dest = ft_split(get_env_value("PATH", li), ':');
	if (!*dest)
		return ;
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
