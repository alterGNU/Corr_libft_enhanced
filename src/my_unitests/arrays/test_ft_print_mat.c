// =============================================================================
// TESTS INT MATRIX FUNCTIONS:
// 
// This program calls init,print and free functions of int matrix and redir the
// standart outputs in a newly created file:
//  - tests/log/<date>/<time>/ft_print_mat/ft_print_mat.txt
// This newly created file is then compared with the provide file:
//  - tests/src/my_unitests/docs/ft_print_mat.txt
// file that contains the expected outputs.
// If they're identical, the program returns 0, else it returns 1.
//
// - TESTED CASES (diff. args combinaisions):
//   - int	*ft_init_mat(int row, int col)
//     - row <= 0 ---------------> should return NULL
//     - col <= 0 ---------------> should return NULL
//   - int ft_print_mat(int *tab, int size)
//     - mat == NULL
//       - row < 0 --------------> should print "(NULL)"
//       - col == 0 -------------> should print "(NULL)"
//       - |row - 1 && col -1| --> should print "(NULL)"
//       - row && col -----------> should print "(NULL)"
//     - tab != NULL
//       - row < 0 --------------> should print "(NULL)"
//       - col == 0 -------------> should print "(NULL)" 
//       - |row - 1 && col -1| --> depends on rows and cols values
//       - row && col -----------> depends on rows and cols values
//   - void ft_free_mat(int **add_tab)
//     - add_tab == NULL --------> should not double free!(use valgrind)
//     - add_tab != NULL --------> should free and set at NULL variable
// =============================================================================
 
// =[ INCLUDE ]=================================================================
#include "libft.h"    // ft_init_mat, ft_print_mat, ft_free_mat
                      // include <unistd.h> --> dup2
#include <string.h>   // strcmp
#include <stdio.h>    // printf, fflush
#include <fcntl.h>    // open, close
#include <sys/stat.h> // struct stat (use in is_a_{file, folder})
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "ft_print_mat"
#define PASS " ✅\n"
#define	FAIL " ❌\n"
#define	S1 "="
#define	S2 "-"
#define	S3 "."
#define	S4 "*"
#define USAGE "\nUSAGE: this programm need 2 arguments\n - arg1: path/folder where to find real.txt\n - arg2: path/folder where to create ft.txt\n"
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
/**
 * open files <file1> and <file2>, compare them bytes by bytes then closes them.
 * @param file1	: const char *, path to file 1.
 * @param file2	: const char *, path to file 2.
 * @return		: 0 if files identical, 1 else.
 */
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
	printf(S1);
	int psf = printf("[ %s ]", title);
	printntime(S1, LEN - psf - 1);
	printf("\n");
}
// -[ PRINT_SUB_TITLE ]---------------------------------------------------------
static void print_subtitle(char *subtitle)
{
	printf(S2);
	int psf = printf("( %s )", subtitle);
	printntime(S2, LEN - psf - 1);
	printf("\n");
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

/**
 * Checks the output of ft_print_mat with given args.
 */
int	**check_init_int_mat(int row, int col, int *nb_err, int expect_null)
{
	int psf = printf("ft_init_mat(%d, %d) ", row, col);
	int	**res = ft_init_mat(row, col);
	if (expect_null == 0)
	{
		psf += printf("-> expect NULL ");
		printntime(S3, LEN - psf - 3);
		if (!res)
			printf(PASS);
		else
		{
			printf(FAIL);
			*nb_err += 1;
		}
	}
	else
	{
		psf += printf("-> expect NOT NULL matrix ");
		printntime(S3, LEN - psf - 3);
		if (res)
			printf(PASS);
		else
		{
			printf(FAIL);
			*nb_err += 1;
		}
	}
	return (res);
}

void check_free_mat(int ***add, int row, int *nb_err)
{
	int psf = printf("ft_free_mat(&m1)-->should not double free, then set at NULL");
	ft_free_mat(add, row);
	printntime(S3, LEN - psf - 3);
	if (!*add)
		printf(PASS);
	else
	{
		printf(FAIL);
		*nb_err += 1;
	}
	fflush(stdout);
}
/**
 * Test init, print and free matrix 
 * expect_init_null: 1 if init should return NULL, 0 else.
 */
void	test_matrix(int row, int col, int *add_nb_err, int expect_init_null)
{
	// test ft_init_int_mat() returns null
	printf("\n");
	int psf = printf(S4" CASE: mat[%d][%d] ", row, col);
	printntime(S4, LEN - psf);
	printf("\n");
	fflush(stdout);
	int **mat = check_init_int_mat(row, col, add_nb_err, expect_init_null);

	// ft_print_int_mat()
	printf("ft_print_mat(m1, %d, %d):\n", -1, col);
	fflush(stdout);
	ft_print_mat(mat, -1, col);

	printf("ft_print_mat(m1, %d, %d):\n", row, 0);
	fflush(stdout);
	ft_print_mat(mat, row, 0);

	printf("ft_print_mat(m1, %d, %d):\n", row - 1, col - 1);
	fflush(stdout);
	ft_print_mat(mat, row - 1, col - 1);

	printf("ft_print_mat(m1, %d, %d):\n", row, col);
	fflush(stdout);
	ft_print_mat(mat, row, col);

	// test ft_free_int_mat() set tab_neg at NULL
	check_free_mat(&mat, row, add_nb_err);
	printntime(S4, LEN);
	printf("\n");
	fflush(stdout);
}

// =[ TESTS FUNCTIONS ]=========================================================
int	main(int ac, char **av)
{
	int	nb_err = 0;

	// -[ 	"0| CREATE VAR FOR FILE COMPARAISON ]-------------------------------
	// handle wrong script args. --> av[1], av[2] need to be folders!
	if (ac != 3)
		return (fprintf(stderr, USAGE), 1);
	if (!is_a_folder(av[1]))
		return (fprintf(stderr, USAGE), 1);
	if (!is_a_folder(av[2]))
		return (fprintf(stderr, USAGE), 1);
	// Build then open real file: fname=<docs_folder_path>+<function_name>.txt
	char *fname = strdup("/ft_print_mat.txt");
	if (!fname)
		return (perror("ERROR:strdup():"), 1);
	char *real = calloc(strlen(av[1]) + strlen(fname) + 1, 1);
	if (!real)
		return (free(fname), perror("ERROR:calloc():"), 1);
	strcpy(real, av[1]);
	strcat(real, fname);
	if (!is_a_file(real))
		return (fprintf(stderr, "ERROR:\"%s\" Not found\n%s", real, USAGE), free(real), 1);
	// Build then open new file: fname=<log_folder_path>+<function_name>.txt
	char *ft = calloc(strlen(av[2]) + strlen(fname) + 1, 1);
	if (!ft)
		return (free(real), free(fname), perror("ERROR:calloc():"), 1);
	strcpy(ft, av[2]);
	strcat(ft, fname);
	free(fname);
	int fd = open(ft, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("main()->open():"), 1);
	// redirect to file stdout (erace > == O_TRUNC)
	dup2(fd, STDOUT_FILENO);

	// -[ 	"A| NOT VALID ARGUMENT ]--------------------------------------------
	print_title("A| Init on WRONG args-->NULL, then print and free on NULL mat:");

	print_subtitle("A.1| Init(row < 0 || col < 0)-->NULL, then print and free on NULL:");
	test_matrix(-1, 3, &nb_err, 0);
	test_matrix(3, -1, &nb_err, 0);
	test_matrix(-1, -1, &nb_err, 0);
	print_sep(S2);

	print_subtitle("A.2| Init(row == 0 || col == 0)-->NULL, then print and free on NULL:");
	test_matrix(0, 5, &nb_err, 0);
	test_matrix(5, 0, &nb_err, 0);
	test_matrix(0, 0, &nb_err, 0);
	print_sep(S2);

	print_sep(S1);

	// -[ 	"B| VALID ARGUMENT ]----------------------------------------------------
	print_title("B| Init on VALID args-->VALID matrix, then print, set and free:");

	print_subtitle("B.1| Init, print and free on not setted matrix (all zeros):");
	test_matrix(1, 1, &nb_err, 1);
	test_matrix(6, 1, &nb_err, 1);
	test_matrix(1, 6, &nb_err, 1);
	test_matrix(5, 5, &nb_err, 1);
	test_matrix(8, 5, &nb_err, 1);
	test_matrix(5, 8, &nb_err, 1);
	print_sep(S2);

	print_sep(S1);
	
// =[  ]========================================================================
	fflush(stdout);
	close(fd);
	if (!is_a_file(ft))
		return (fprintf(stderr, "ERROR:\"%s\" Not created\n%s", ft, USAGE), free(ft), free(real), 1);
	nb_err += compare_files(ft,real);
	return (free(ft), free(real), nb_err);
}
