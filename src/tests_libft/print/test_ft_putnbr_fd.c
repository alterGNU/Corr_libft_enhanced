#include "libft.h"
#include <fcntl.h>  // open, close
#include <stdio.h>  // perror
#include <string.h> // strcmp
#include <limits.h> // INT_MIN

int	create_file(const char *filename, int nb)
{
	FILE *file = fopen(filename, "w");
	if (!file)
		return (1);
	int fd = fileno(file);
    if (fd == -1) {
        perror("open");
        return (1);
    }
	
	ft_putnbr_fd(nb, fd);

	if (close(fd) == -1) {
		perror("close");
		return (1);
	}
	return (0);
}

int compare_files(const char *file1, const char *file2)
{
    FILE *f1 = fopen(file1, "r");
	if (!f1)
		return (1);
    FILE *f2 = fopen(file2, "r");
	if (!f2)
	{
		fclose(f1);
		return (1);
	}

    if (!f1 || !f2)
	{
        perror("Erreur lors de l'ouverture des fichiers");
        return (1);
    }

    while (1) {
        int byte1 = fgetc(f1);
        int byte2 = fgetc(f2);

        if (byte1 != byte2)
            return (1);     // Les fichiers sont différents

        if (byte1 == EOF || byte2 == EOF)
		{
            if (byte1 != EOF || byte2 != EOF)
                return (1); // Les fichiers ont des tailles différentes
            break;
        }
    }

    fclose(f1);
    fclose(f2);
    return (0);
}

int	main()
{
	int	tot_fail=0;

	tot_fail+=create_file("retour_ft_putnbr_fd_zero.txt", 0);
	tot_fail+=compare_files("retour_ft_putnbr_fd_zero.txt","docs/ft_putnbr_fd_zero.txt");
	tot_fail+=create_file("retour_ft_putnbr_fd_intmax.txt", INT_MAX);
	tot_fail+=compare_files("retour_ft_putnbr_fd_intmax.txt","docs/ft_putnbr_fd_intmax.txt");
	tot_fail+=create_file("retour_ft_putnbr_fd_intmin.txt", INT_MIN);
	tot_fail+=compare_files("retour_ft_putnbr_fd_intmin.txt","docs/ft_putnbr_fd_intmin.txt");

	return (tot_fail);
}
