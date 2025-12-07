// =[ INCLUDE ]=================================================================
#include "libft.h"    // ft_init_int_array, ft_print_int_array, ft_free_int_array
#include <string.h>   // strcmp
#include <stdio.h>    // printf, fflush
#include <fcntl.h>    // open, close
#include <sys/stat.h> // struct stat (use in is_a_{file, folder})
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "ft_print_int_array"
#define E "\033[0m"       // COLOR END
#define CR "\033[0;31m"   // COLOR RED
#define CV "\033[0;32m"   // COLOR GREEN
#define CM "\033[0;33m"   // COLOR BROWN
#define CY "\033[0;93m"   // COLOR YELLOW
#define CB "\033[0;36m"   // COLOR AZURE
#define CG "\033[0;37m"   // COLOR GREY
#define CT "\033[97;100m" // COLOR GREY
#define PASS " \033[37;42m ✓ \033[0m\n"
#define	FAIL " \033[30;41m ✗ \033[0m\n"
#define	S1 CT"="E
#define	S2 CB"*"E
#define	S3 "-"
#define USAGE "\nUSAGE: this programm need 2 arguments\n   - arg1: path/folder where to find real.txt\n   - arg2: path/folder where to create ft.txt\n"
// =[ UTILS FUN ]===============================================================
// -[ IS_A_FOLDER ]-------------------------------------------------------------
static int	is_a_folder(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}
// -[ IS_A_FILE ]---------------------------------------------------------------
static int	is_a_file(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISREG(st.st_mode))
		return (1);
	return (0);
}
// -[ COMPARE_FILES ]-----------------------------------------------------------
int compare_files(const char *file1, const char *file2)
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
// -[ PRINTNTIME ]--------------------------------------------------------------
static int	printntime(char *str, int n)
{
	for (int i = 0 ; i < n; i++)
		printf("%s", str);
	return (n);
}
// -[ PRINT_TITLE ]-------------------------------------------------------------
static void print_title(char *title)
{
	printf(S1""CT);
	int psf = printf("[ %s ]", title);
	printntime(S1, LEN - psf - 1);
	printf(E"\n");
}
// -[ PRINT_SUB_TITLE ]---------------------------------------------------------
static void print_subtitle(char *subtitle)
{
	printf(S2""CB);
	int psf = printf("( %s )", subtitle);
	printntime(S2, LEN - psf - 1);
	printf(E"\n");
}
// -[ PRINT_SEP ]---------------------------------------------------------------
static void print_sep(char *sep)
{
	int	i = -1;
	while (++i < LEN)
		printf("%s", sep);
	printf("\n\n");
}
// -[ COUNT_CHAR_IN_STR ]-------------------------------------------------------
//static int	count_char_in_str(char c, char *str)
//{
//	int	res;
//
//	res = 0;
//	while(*str)
//	{
//		if (*str == c)
//			res++;
//		str++;
//	}
//	return (res);
//}

// =[ TESTS FUNCTIONS ]=========================================================
int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	(void) ev;
	char	*fname;
	char	*real;
	char	*ft;
	int		fd;
	int	nb_err = 0;
	int	psf = 0;

	// -[ 	"0| CREATE VAR FOR FILE COMPARAISON ]-------------------------------
	if (ac != 3)
		return (fprintf(stderr, USAGE), 1);
	if (!is_a_folder(av[1]))
		return (fprintf(stderr, USAGE), 1);
	if (!is_a_folder(av[2]))
		return (fprintf(stderr, USAGE), 1);
	// construct real_filename.txt then open it.
	fname = strdup("/ft_print_int_array.txt");
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

	// -[ 	"A| NOT VALID ARGUMENT ]--------------------------------------------
	print_title("A| Init, print and free on NULL or WRONG args:");

	print_subtitle("A.1| Init, print and free a NEGATIVE SIZE:");
	int	*tab_neg = ft_init_int_array(-5);
	fflush(stdout);
	int r_neg = ft_print_int_array(tab_neg, -5);
	psf += r_neg;
	psf += printf(" --> (%d)", r_neg);
	printntime(" ", LEN - psf - 4);
	if (r_neg == 6 && !tab_neg)
		printf(PASS);
	else
	{
		printf(FAIL);
		nb_err++;
	}
	psf = 0;
	ft_free_int_array(&tab_neg);
	print_sep(S2);

	print_subtitle("A.2| Init, print and free a NULL INT SIZE:");
	int	*tab_null = ft_init_int_array(0);
	fflush(stdout);
	int r_null = ft_print_int_array(tab_null, 0);
	psf += r_null;
	psf += printf(" --> (%d)", r_null);
	printntime(" ", LEN - psf - 4);
	if (r_null == 6 && !tab_null)
		printf(PASS);
	else
	{
		printf(FAIL);
		nb_err++;
	}
	psf = 0;
	ft_free_int_array(&tab_null);
	print_sep(S2);
	print_sep(S1);

	print_title("B| Init, print and free on GOOD args:");

	print_subtitle("B.1| size=6, then set to [0,1,2,3,4,5]:");
	int	*tab1 = ft_init_int_array(6);
	fflush(stdout);
	int r1 = ft_print_int_array(tab1, 6);
	psf += r1;
	psf += printf(" --> (%d)", r1);
	printntime(" ", LEN - psf - 4);
	if (r1 == 18 && tab1)
		printf(PASS);
	else
	{
		printf(FAIL);
		nb_err++;
	}
	printf("\n");
	psf = 0;
	for (int i = 0; i < 6; i++)
		tab1[i] = i;
	fflush(stdout);
	r1 = ft_print_int_array(tab1, 6);
	psf += r1;
	psf += printf(" --> (%d)", r1);
	printntime(" ", LEN - psf - 4);
	if (r1 == 18 && tab1)
		printf(PASS);
	else
	{
		printf(FAIL);
		nb_err++;
	}
	psf = 0;
	ft_free_int_array(&tab1);
	print_sep(S2);

	print_subtitle("B.2| size=6, then set to [1, 10, 100, 1000, 10000, 100000]:");
	int	*tab2 = ft_init_int_array(6);
	fflush(stdout);
	int r2 = ft_print_int_array(tab2, 6);
	psf += r2;
	psf += printf(" --> (%d)", r2);
	printntime(" ", LEN - psf - 4);
	if (r2 == 18 && tab2)
		printf(PASS);
	else
	{
		printf(FAIL);
		nb_err++;
	}
	printf("\n");
	psf = 0;
	for (int i = 0; i < 6; i++)
	{
		tab2[i] = 1;
		for (int j = 0; j < i; j++)
			tab2[i] *= 10;
	}
	fflush(stdout);
	r2 = ft_print_int_array(tab2, 6);
	psf += r2;
	psf += printf(" --> (%d)", r2);
	printntime(" ", LEN - psf - 4);
	if (r2 == 33 && tab2)
		printf(PASS);
	else
	{
		printf(FAIL);
		nb_err++;
	}
	psf = 0;
	ft_free_int_array(&tab2);
	print_sep(S2);
	// Close
	fflush(stdout);
	close(fd);
	if (!is_a_file(ft))
		return (fprintf(stderr, "ERROR:\"%s\" Not created\n%s", ft, USAGE), free(ft), free(real), 1);
	nb_err += compare_files(ft,real);
	return (free(ft), free(real), nb_err);
}
