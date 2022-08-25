#include "minishell.h"
/*int	count_heredoc(t_lst *li)
{
	int	ret;
	t_cmd 	*temp;
	t_redir *red;

	temp = li->head;
	ret = 0;
	while (temp)
	{	
		red = temp->redir;
		while (red)
		{
			if (red->sign == HEREDOC)
				ret++;
			red = red->next;
		}
		temp = temp->next;
	}
	li->heredoc = ret;
	if (ret)
		return (1);
	return (0);
}*/

void	zero_newline(char **old)
{
	char	*s;
	int	i;
	
	if (*old[0] == '\n')
		return ;
	s = ft_strdup(*old);
	free(*old);
	i = -1;
	while (s[++i] && s[i] != '\n')
		;
	s[i] = '\0';
	*old = s;
}

int	process_heredoc(t_redir *red, int *file_temp)
{
	char	*temp;
	
	write(1, "> ", 2);
	temp = get_next_line(0);
	if (!temp)
		exit(1);
	zero_newline(&temp);
	if (ft_strcmp(red->name, temp) != 0)
	{
		write(*file_temp, temp, ft_strlen(temp));
		write(*file_temp, "\n", 1);
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

int	here_doc(t_redir *red)
{
	int	file_temp;

	file_temp = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file_temp < 0)
		msg_error("Error: file_temp_here_doc\n", 0, NULL);
	while (process_heredoc(red, &file_temp))
		;
	close(file_temp);
	return (1);
}
