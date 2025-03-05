#include "libft.h"
#include <fcntl.h>  // open, close
#include <stdio.h>  // perror
#include <string.h> // strcmp

int	create_file(const char *filename, char *txt)
{
	FILE *file = fopen(filename, "w");
	if (!file)
		return (1);
	int fd = fileno(file);
    if (fd == -1) {
        perror("open");
        return (1);
    }
	
	ft_putstr_fd(txt, fd);

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

	char txt[]="coucou\tpetite\vperruche\n";
	tot_fail+=create_file("retour_ft_putstr_fd.txt", txt);
	tot_fail+=compare_files("retour_ft_putstr_fd.txt","docs/ft_putstr_fd.txt");

	return (tot_fail);
}
