#include "libft.h"    // ft_putendl_fd
#include <fcntl.h>    // open, close
#include <stdio.h>    // fprintf, printf
#include <errno.h>    // perror, errno
#include <string.h>   // strcmp
#include <sys/stat.h> // struct stat (use in is_a_{file, folder})

#define USAGE "\nUSAGE: this programm need 2 arguments\n   - arg1: path/folder where to find real.txt\n   - arg2: path/folder where to create ft.txt\n"

static int	is_a_folder(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

static int	is_a_file(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISREG(st.st_mode))
		return (1);
	return (0);
}

static int	create_file(const char *filename, char *txt)
{
	FILE *file = fopen(filename, "w");
	if (!file)
		return (perror("ERROR open():"), 1);
	int fd = fileno(file);
	if (fd == -1)
    	return (perror("ERROR fileno():"), fclose(file), 1);
	ft_putendl_fd(txt, fd);
	if (fclose(file) == EOF)
		return (perror("fclose"), 1);
	return (0);
}

static int compare_files(const char *file1, const char *file2)
{
    FILE *f1 = fopen(file1, "r");
	if (!f1)
		return (perror("ERROR compare_file()->fopen(f1)"), 1);
    FILE *f2 = fopen(file2, "r");
	if (!f2)
		return (perror("ERROR compare_file()->fopen(f2)"), 1);

    while (1)
	{
        int byte1 = fgetc(f1);
        int byte2 = fgetc(f2);

        if (byte1 != byte2)
			return (fprintf(stderr,"File '%s' != '%s' [differ by containt]\n", file1, file2), fclose(f1), fclose(f2), 1);

        if (byte1 == EOF || byte2 == EOF)
		{
            if (byte1 != EOF || byte2 != EOF)
				return (fprintf(stderr,"File '%s' != '%s' [differ by size]\n", file1, file2), fclose(f1), fclose(f2), 1);
            break;
        }
    }
	return (fclose(f1), fclose(f2), 0);
}

int	main(int ac, char **av)
{
	char	*str;
	char	*filename;
	char	*real;
	char	*ft;
	int		nb_err;

	if (ac != 3)
		return (fprintf(stderr, USAGE), 1);
	if (!is_a_folder(av[1]))
		return (fprintf(stderr, USAGE), 1);
	if (!is_a_folder(av[2]))
		return (fprintf(stderr, USAGE), 1);

	filename = strdup("/ft_putendl_fd.txt");
	if (!filename)
		return (perror("ERROR:strdup():"), 1);
	real = calloc(strlen(av[1]) + strlen(filename) + 1, 1);
	if (!real)
		return (free(filename), perror("ERROR:calloc():"), 1);
	strcpy(real, av[1]);
	strcat(real, filename);
	if (!is_a_file(real))
		return (fprintf(stderr, "ERROR:\"%s\" Not found\n%s", real, USAGE), free(real), 1);
	ft = calloc(strlen(av[2]) + strlen(filename) + 1, 1);
	if (!ft)
		return (free(real), free(filename), perror("ERROR:calloc():"), 1);
	strcpy(ft, av[2]);
	strcat(ft, filename);
	free(filename);
	str = strdup("Le gras c'est la vie!");
	if (!str)
		return (free(real), free(ft), perror("ERROR:strdup():"), 1);
	if (create_file(ft, str))
		return (free(str), free(real), free(ft), perror("Error:create_file(ft)"), 1);
	if (!is_a_file(ft))
		return (fprintf(stderr, "ERROR:\"%s\" Not created\n%s", ft, USAGE), free(str), free(ft), free(real), 1);
	nb_err = compare_files(ft,real);
	return (free(str), free(ft), free(real), nb_err);
}
