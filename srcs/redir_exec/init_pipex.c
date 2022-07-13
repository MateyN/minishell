/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:43:19 by rmamison          #+#    #+#             */
/*   Updated: 2022/07/13 17:20:29 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_redirection(t_lst	*li)
{
	if (li->heredoc == 1)
		here_doc(argc, argv, pipex);
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
			msg_error("Error: infile");
		pipex->outfile = open(argv[argc - 1], \
				O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (pipex->outfile < 0)
			msg_error("Error: outfile");
	}
	pipex->path = NULL;
	pipex->cmd = NULL;
	pipex->nb_cmd = argc - (3 + pipex->here_doc);
	pipex->nb_pipe = 2 * (pipex->nb_cmd - 1);
	pipex->cmd_arg = NULL;
}

static void	pipe_init(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd - 1)
	{
		if (pipe(pipex->tube + (i * 2)) < 0)
		{
			free_pipex(pipex, ALL);
			msg_error("Error: pipe_init");
		}
		i++;
	}
}
