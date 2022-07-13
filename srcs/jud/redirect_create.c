# include "minishell.h"

void	init_output(test, flag_> or flag_>>)
{
	//redirige sortie standard in a file
	if (flag == ">")
		test->output = open(argv, O_TRUNC | O_CREAT | O_RDWR, 0644);
	else if (flag == ">>")
		test->output = open(argv, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (test->output < 0)
		msg_error("minishell: error outfile", 0, N
}

void	init_input(test, flag_< or flag_<<)
{
	if (flag == "<") //redirige entrer standard de cmd in the file => cmd < file 
	{
	
	}
	else if (flag == "<<") //heredoc
	{
	
	}
}
