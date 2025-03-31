#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	// Check number of argument.
	if (ac != 2)
		return (perror("Error:Wrong usage of test0_get_next_line.c, need only one arg:path to file to read"), 1);
	// Check if arg is a readable file
	if (access(av[1], R_OK))
		return (perror("Error:Arg is not a READABLE FILE"), 1);
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
