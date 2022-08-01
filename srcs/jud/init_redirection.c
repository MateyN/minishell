#include "minishell.h"

int	std_in_out(t_lst *li, t_redir *redir)
{
	if (redir->sign == REDIR_IN)
		li->infile = open(redir->name, O_RDONLY);
	else if (redir->sign == REDIR_OUT_S)
		li->outfile = open(redir->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->sign == REDIR_OUT_D)
		li->outfile = open(redir->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (li->infile < 0 || li->outfile < 0)
	{
		if (redir->sign == REDIR_IN)
		{
			msg_error("minishell: ", 0, redir->name);
			write(2, ": No such file or directory\n", 28);
		}
		else
			msg_error("Error: outfile", 0, "\n");
		return (0);
	}
	if (li->infile > 0 || li->outfile > 0)
		redir->sign = 0;
	return (1);
}
