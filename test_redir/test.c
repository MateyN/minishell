#include <unistd.h>
#include <string.h>

int	main(int ac, char **av)
{
	if (ac <= 1)
		write(1, "miss arg\n", 8);
	else{
		write(1, av[2], strlen(av[2]));
		write(1, "\n", 1);}
	return (0);
}
