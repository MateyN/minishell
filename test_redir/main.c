#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	int pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		int file = open(av[3], O_CREAT | O_WRONLY , 0644);
		if (file == -1)
			return (-1);
		dup2(file, STDOUT_FILENO);
		close(file);
		if (execv(av[1], av) == -1)
		{
			write(1, "error", 5);
			return (-1);
		}
	}
	int status;
	wait(&status);
	return (0);
}
