#include "libft.h"    // ft_putnbr_fd
#include <fcntl.h>    // open, close
#include <stdio.h>    // fprintf, printf
#include <errno.h>    // perror, errno
#include <string.h>   // strcmp
#include <sys/stat.h> // struct stat (use in is_a_{file, folder})
#include <limits.h>   // INT_MAX, INT_MIN

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

static int	create_file(const char *filename, int nb)
{
	FILE *file = fopen(filename, "w");
	if (!file)
		return (perror("ERROR open():"), 1);
	int fd = fileno(file);
	if (fd == -1)
    	return (perror("ERROR fileno():"), fclose(file), 1);
	ft_putnbr_fd(nb, fd);
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

static int	test(const char *find, const char *create, const char *name, int n)
{
	char	*rl_fname;
	char	*real;
	char	*ft_fname;
	char	*ft;
	int		nb_err;

	rl_fname = calloc(23 + strlen(name) + 1, 1);
	if (!rl_fname)
		return (perror("ERROR:calloc():"), 1);
	strcpy(rl_fname, "/ft_putnbr_fd_");
	strcat(rl_fname, name);
	strcat(rl_fname, "_real.txt");
	real = calloc(strlen(find) + strlen(rl_fname) + 1, 1);
	if (!real)
		return (free(rl_fname), perror("ERROR:calloc():"), 1);
	strcpy(real, find);
	strcat(real, rl_fname);
	free(rl_fname);
	if (!is_a_file(real))
		return (fprintf(stderr, "ERROR:\"%s\" Not found\n%s", real, USAGE), free(real), 1);
	ft_fname = calloc(21 + strlen(name) + 1, 1);
	if (!ft_fname)
		return (perror("ERROR:calloc():"), 1);
	strcpy(ft_fname, "/ft_putnbr_fd_");
	strcat(ft_fname, name);
	strcat(ft_fname, "_ft.txt");
	ft = calloc(strlen(create) + strlen(ft_fname) + 1, 1);
	if (!ft)
		return (free(ft_fname), perror("ERROR:calloc():"), 1);
	strcpy(ft, create);
	strcat(ft, ft_fname);
	free(ft_fname);
	printf("find='%s'\ncreate='%s'\n", real, ft);
	if (create_file(ft, n))
		return (free(real), free(ft), perror("Error:create_file(ft)"), 1);
	if (!is_a_file(ft))
		return (fprintf(stderr, "ERROR:\"%s\" Not created\n%s", ft, USAGE), free(ft), free(real), 1);
	nb_err = compare_files(ft, real);
	return (free(ft), free(real), nb_err);
}

int	main(int ac, char **av)
{
	int		nb_err;

	if (ac != 3)
		return (fprintf(stderr, USAGE), 0);
	if (!is_a_folder(av[1]))
		return (fprintf(stderr, USAGE), 0);
	if (!is_a_folder(av[2]))
		return (fprintf(stderr, USAGE), 0);
	nb_err = test(av[1], av[2], "zero", 0);
	nb_err+= test(av[1], av[2], "intmin", INT_MIN);
	nb_err+= test(av[1], av[2], "intmax", INT_MAX);
	return (nb_err);
}

//int	main()
//{
//
//	tot_fail+=create_file("retour_ft_putnbr_fd_zero.txt", 0);
//	tot_fail+=compare_files("retour_ft_putnbr_fd_zero.txt","docs/ft_putnbr_fd_zero.txt");
//	tot_fail+=create_file("retour_ft_putnbr_fd_intmax.txt", INT_MAX);
//	tot_fail+=compare_files("retour_ft_putnbr_fd_intmax.txt","docs/ft_putnbr_fd_intmax.txt");
//	tot_fail+=create_file("retour_ft_putnbr_fd_intmin.txt", INT_MIN);
//	tot_fail+=compare_files("retour_ft_putnbr_fd_intmin.txt","docs/ft_putnbr_fd_intmin.txt");
//
//	return (tot_fail);
//}
