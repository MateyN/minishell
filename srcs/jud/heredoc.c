#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	str1;
	unsigned char	str2;

	while (1)
	{
		str1 = (unsigned char) *s1++;
		str2 = (unsigned char) *s2++;
		if (str1 != str2)
			return (str1 - str2);
		if (str1 == '\0')
			return (0);
	}
	return (0);
}/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:17:25 by rmamison          #+#    #+#             */
/*   Updated: 2022/07/13 17:20:27 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	file_in_out(t_lst *li)
{

	li->redir->limiter = open(path, O_RDONLY);
	if (pipex->infile < 0)
	{	
		unlink(path);
		msg_error("Error: infile");
	}
	li->redir->outfile = open(li->redir, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (pipex->outfile < 0)
		msg_error("Error: outfile");
}
*/

void	here_doc(t_lst *li)
{
	int	file_temp;
	char	*temp;
	int	i;

	file_temp = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file_temp < 0)
		msg_error("Error: file_temp_here_doc\n", 0, NULL);
	i = 0;
	temp = NULL;
	while (1)
	{
		write(1, "> ", 2);
		temp = get_next_line(0);
		if (!temp)
			exit(1);
		if (!ft_strcmp(li->redir->limiter[i], temp))
		{
			printf("je pass \n");
			i++;
			if (!li->redir->limiter[i])
				break ;
		}
		write(file_temp, temp, ft_strlen(temp));
		write(file_temp, "\n", 1);
		free(temp);
	}
	if (temp)
		free(temp);
	close(file_temp);
	//file_in_out(argv[argc - 1], ".heredoc", pipex);
}
