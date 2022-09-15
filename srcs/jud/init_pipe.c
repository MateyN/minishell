/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:06:59 by rmamison          #+#    #+#             */
/*   Updated: 2022/09/11 22:12:18 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(t_lst *li)
{
	int	i;

	li->tube_fd = (int **)malloc(sizeof(int *) * li->pipe);
	if (!li->tube_fd)
	{
		msg_error("error: allocaion tube_fd\n", 0, NULL);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < li->pipe)
	{
		if (!(li->tube_fd[i] = malloc(sizeof(int) * 2)))
		{
			msg_error("error: allocation *tube_fd\n", 0, NULL);
			exit(EXIT_FAILURE);
		}
		if (pipe(li->tube_fd[i]) == -1)
		{
			free_pipe(li);
			msg_error("Error: function pipe\n", 0, NULL);
		}
	}
}
