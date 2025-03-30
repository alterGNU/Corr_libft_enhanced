#include "libft.h"    // ft_print_str_array, ft_free_str_array
#include <fcntl.h>    // open, close
#include <stdio.h>    // fprintf, printf, fopen, fclose
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
	char	*fname;
	char	*real;
	char	*ft;
	int		nb_err;
	int		fd;
	char	**tab0;
	char	**tab1;
	char	**tab2;
	char	**tab3;
	int		r0;
	int		r1;
	int		r2;
	int		r3;

	if (ac != 3)
		return (fprintf(stderr, USAGE), 1);
	if (!is_a_folder(av[1]))
		return (fprintf(stderr, USAGE), 1);
	if (!is_a_folder(av[2]))
		return (fprintf(stderr, USAGE), 1);
	// construct real_filename.txt then open it.
	fname = strdup("/ft_free_str_array.txt");
	if (!fname)
		return (perror("ERROR:strdup():"), 1);
	real = calloc(strlen(av[1]) + strlen(fname) + 1, 1);
	if (!real)
		return (free(fname), perror("ERROR:calloc():"), 1);
	strcpy(real, av[1]);
	strcat(real, fname);
	if (!is_a_file(real))
		return (fprintf(stderr, "ERROR:\"%s\" Not found\n%s", real, USAGE), free(real), 1);
	// construct ft_filename.txt then create it.
	ft = calloc(strlen(av[2]) + strlen(fname) + 1, 1);
	if (!ft)
		return (free(real), free(fname), perror("ERROR:calloc():"), 1);
	strcpy(ft, av[2]);
	strcat(ft, fname);
	free(fname);
	fd = open(ft, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("main()->open():"), 1);
	// redirect to file stdout (erace > == O_TRUNC)
	dup2(fd, STDOUT_FILENO);
	// Tests tab0
	ft_printf("Before:tab0=");
	tab0 = NULL;
	r0 = ft_print_str_array(tab0);
	ft_printf("-->(%d)\n", r0);
	ft_free_str_array(&tab0);
	ft_printf("After :tab0=");
	r0 = ft_print_str_array(tab0);
	ft_printf("-->(%d)\n", r0);
	// Tests tab1
	tab1 = calloc(1, sizeof(char *));
	if (!tab1)
		return (perror("main()->tab1 = calloc():"), 1);
	ft_printf("Before:tab1=");
	r1 = ft_print_str_array(tab1);
	ft_printf("-->(%d)\n", r1);
	ft_free_str_array(&tab1);
	ft_printf("After :tab1=");
	r1 = ft_print_str_array(tab1);
	ft_printf("-->(%d)\n", r1);
	// Tests tab2
	tab2 = calloc(2, sizeof(char *));
	if (!tab2)
		return (perror("main()->tab2 = calloc():"), 1);
	ft_printf("Before:tab2=");
	tab2[0] = strdup("coucou petite perruche!");
	r2 = ft_print_str_array(tab2);
	ft_printf("-->(%d)\n", r2);
	ft_free_str_array(&tab2);
	ft_printf("After :tab2=");
	r2 = ft_print_str_array(tab2);
	ft_printf("-->(%d)\n", r2);
	// Tests tab3
	tab3 = calloc(5, sizeof(char *));
	if (!tab3)
		return (perror("main()->tab3 = calloc():"), 1);
	ft_printf("Before:tab3=");
	tab3[0] = strdup("coucou");
	if (!tab3[0])
		return (perror("main()->tab3[0] = strdup():"), free(tab3), 1);
	tab3[1] = strdup("petite");
	if (!tab3[1])
		return (perror("main()->tab3[1] = strdup():"), ft_free_str_array(&tab3), 1);
	tab3[2] = strdup("perruche");
	if (!tab3[2])
		return (perror("main()->tab3[2] = strdup():"), ft_free_str_array(&tab3), 1);
	tab3[3] = strdup("!");
	if (!tab3[3])
		return (perror("main()->tab3[3] = strdup():"), ft_free_str_array(&tab3), 1);
	r3 = ft_print_str_array(tab3);
	ft_printf("-->(%d)\n", r3);
	ft_free_str_array(&tab3);
	ft_printf("After :tab3=");
	r3 = ft_print_str_array(tab3);
	ft_printf("-->(%d)\n", r3);
	// Close
	close(fd);
	if (!is_a_file(ft))
		return (fprintf(stderr, "ERROR:\"%s\" Not created\n%s", ft, USAGE), free(ft), free(real), 1);
	nb_err = compare_files(ft,real);
	return (free(ft), free(real), nb_err);
}
