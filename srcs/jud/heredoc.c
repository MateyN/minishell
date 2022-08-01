#include "minishell.h"

void	zero_newline(char **old)
{
	char	*s;
	int	i;
	
	s = ft_strdup(*old);
	free(*old);
	i = -1;
	while (s[++i] && s[i] != '\n')
		;
	s[i] = '\0';
	*old = s;
}

int	count_heredoc(t_lst *li)
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
	return (ret);
}

int	push_redir(t_cmd **node, t_redir **ret_redir, int flag)
{
	t_redir	*red;
	
	*ret_redir = NULL;
	while (*node)
	{
		red = (*node)->redir;
		while (red && red->sign != flag)
			red = red->next;
		if (!red && flag != HEREDOC)
			return (0);
		if (red && red->sign == HEREDOC && red->name == NULL)
			return (0);
		else if (red && red->sign == flag)
		{
			*ret_redir = red;
			return (1);
		}
		else if (flag == HEREDOC)
			*node = (*node)->next;
	}
	return (0);
}

void	check_limiter(t_redir *red, char *s, int *i, int *time)
{

	if (red->sign == HEREDOC)
	{
		if (ft_strcmp(red->name, s) == 0)
		{
			red->sign = 0;
			(*i)++;
			(*time) = 1;
		}
	}
	return ;
}

int	here_doc(t_cmd *node, int nb)
{
	int	file_temp;
	char	*temp;
	int	i;
	int	time;
	t_cmd	*temp_node;
	t_redir	*node_lim;

	temp_node = node;
	file_temp = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file_temp < 0)
		msg_error("Error: file_temp_here_doc\n", 0, NULL);
	temp = NULL;
	i = 0;
	time = 1;
	while (1)
	{
		if (time  == 1)
		{
			if (!push_redir(&temp_node, &node_lim, HEREDOC))
			{
				ft_putstr_fd("minishell: syntax error near unexpectead token `newline'\n", 2);	
				return (-1);
			}
			time = 0;
		}
		write(1, "> ", 2);
		temp = get_next_line(0);
		zero_newline(&temp);
		if (!temp)
			exit(1);
		check_limiter(node_lim, temp, &i, &time);
		if (i == nb)
			break ;
		write(file_temp, temp, ft_strlen(temp));
		write(file_temp, "\n", 1);
		free(temp);
	}
	if (temp)
		free(temp);
	unlink(".heredoc");
	close(file_temp);
	return (1);
	//file_in_out(argv[argc - 1], ".heredoc", pipex);
}
