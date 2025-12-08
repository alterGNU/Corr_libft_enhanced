// =============================================================================
// TESTS INT_ARRAY FUNCTIONS:
// 
// This program calls init,print and free functions of int array and redir the
// standart outputs in a newly created file:
//  - tests/log/<date>/<time>/ft_print_int_array/ft_print_int_array.txt
// This newly created file is then compared with the provide file:
//  - tests/src/my_unitests/docs/ft_print_int_array.txt
// file that contains the expected outputs.
// If they're identical, the program returns 0, else it returns 1.
//
// - TESTED CASES (diff. args combinaisions):
//   - int	*ft_init_int_array(int size)
//     - size < 0 ---------------> should return NULL
//     - size == 0 --------------> should return NULL
//     - size > 0 ---------------> should return int *tab != NULL
//   - int ft_print_int_array(int *tab, int size)
//     - tab == NULL
//       - size < 0 -------------> should print "(NULL)" and return 6
//       - size == 0 ------------> should print "(NULL)" and return 6
//       - size > 0 -------------> should print "(NULL)" and return 6
//     - tab != NULL
//       - size < 0 -------------> should print "(NULL)" and return 6
//       - 0 < size < real_size -> should print tab[0:size] and return ...
//       - size == real_size ----> should print tab and return ...
//       - size > real_size -----> ⚠️  Undefine Behavior (stack overflows)
//   - void ft_free_int_array(int **add_tab)
//     - add_tab == NULL --------> should not double free!(use valgrind)
//     - add_tab != NULL --------> should free and set at NULL variable
// =============================================================================
 
// =[ INCLUDE ]=================================================================
#include "libft.h"    // ft_init_int_array, ft_print_int_array, ft_free_int_array
                      // include <unistd.h> --> dup2
#include <string.h>   // strcmp
#include <stdio.h>    // printf, fflush
#include <fcntl.h>    // open, close
#include <sys/stat.h> // struct stat (use in is_a_{file, folder})
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "ft_print_int_array"
#define PASS " ✅\n"
#define	FAIL " ❌\n"
#define	S1 "="
#define	S2 "-"
#define	S3 "."
#define USAGE "\nUSAGE: this programm need 2 arguments\n - arg1: path/folder where to find real.txt\n   - arg2: path/folder where to create ft.txt\n"
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

static int check_print_int_array(char *var_name, int *int_arr, int size, int res)
{
	int psf = printf("ft_print_int_array(%s, %d):", var_name, size);
	fflush(stdout);
	int ret_val = ft_print_int_array(int_arr, size);
	psf += ret_val;
	psf += printf(" --> [%d]==[%d]", ret_val, res);
	printntime(S3, LEN - psf - 3);
	if (ret_val == res)
		return (printf(PASS), 0);
	return (printf(FAIL), 1);
}

// =[ TESTS FUNCTIONS ]=========================================================
int	main(int ac, char **av)
{
	int	nb_err = 0;
	int	psf = 0;

	// -[ 	"0| CREATE VAR FOR FILE COMPARAISON ]-------------------------------
	// handle wrong script args. --> av[1], av[2] need to be folders!
	if (ac != 3)
		return (fprintf(stderr, USAGE), 1);
	if (!is_a_folder(av[1]))
		return (fprintf(stderr, USAGE), 1);
	if (!is_a_folder(av[2]))
		return (fprintf(stderr, USAGE), 1);
	// Build then open real file: fname=<docs_folder_path>+<function_name>.txt
	char *fname = strdup("/ft_print_int_array.txt");
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
	print_title("A| Init, print and free on NULL or WRONG args:");

	print_subtitle("A.1| Init, print and free a NEGATIVE SIZE:");
	// test ft_init_int_array() returns null
	psf = printf("tab_neg = ft_init_int_array(-5) <=> NULL");
	int	*tab_neg = ft_init_int_array(-5);
	printntime(S3, LEN - psf - 3);
	if (!tab_neg)
		psf += printf(PASS);
	else
	{
		psf += printf(FAIL);
		nb_err++;
	}

	// ft_print_int_array(tab_neg, -5)
	nb_err += check_print_int_array("tab_neg", tab_neg, -5, 6);
	// ft_print_int_array(tab_neg, 0)
	nb_err += check_print_int_array("tab_neg", tab_neg, 0, 6);
	// ft_print_int_array(tab_neg, 3)
	nb_err += check_print_int_array("tab_neg", tab_neg, 3, 6);
	
	// test ft_free_int_array() set tab_neg at NULL
	psf = printf("ft_free_int_array(&tab_neg)-->free then set at NULL");
	ft_free_int_array(&tab_neg);
	printntime(S3, LEN - psf - 3);
	if (!tab_neg)
		psf += printf(PASS);
	else
	{
		psf += printf(FAIL);
		nb_err++;
	}
	psf = 0;
	print_sep(S2);

	print_subtitle("A.2| Init, print and free a NULL INT SIZE:");
	// test ft_init_int_array() returns null
	psf = printf("tab_null = ft_init_int_array(0) <=> NULL");
	int	*tab_null = ft_init_int_array(0);
	printntime(S3, LEN - psf - 3);
	if (!tab_null)
		psf += printf(PASS);
	else
	{
		psf += printf(FAIL);
		nb_err++;
	}

	// ft_print_int_array(tab_neg, -5)
	nb_err += check_print_int_array("tab_null", tab_null, -5, 6);
	// ft_print_int_array(tab_null, 0)
	nb_err += check_print_int_array("tab_null", tab_null, 0, 6);
	// ft_print_int_array(tab_null, 5)
	nb_err += check_print_int_array("tab_null", tab_null, 5, 6);
	
	// test ft_free_int_array() set tab_null at NULL
	psf = printf("ft_free_int_array(&tab_null)-->free then set at NULL");
	ft_free_int_array(&tab_null);
	printntime(S3, LEN - psf - 3);
	if (!tab_null)
		psf += printf(PASS);
	else
	{
		psf += printf(FAIL);
		nb_err++;
	}
	psf = 0;
	print_sep(S2);
	print_sep(S1);
	
// =[  ]========================================================================
	print_title("B| Init, print and free on GOOD args:");
    // -[  ]--------------------------------------------------------------------
	print_subtitle("B.1| size=6, then set to [0,1,2,3,4,5]:");
	// test ft_init_int_array() returns null
	psf = printf("tab1 = ft_init_int_array(0) <=> [0, 0, 0, 0, 0, 0]");
	fflush(stdout);
	int	*tab1 = ft_init_int_array(6);
	printntime(S3, LEN - psf - 3);
	if (tab1)
		psf += printf(PASS);
	else
	{
		psf += printf(FAIL);
		nb_err++;
	}

	// Print Before setting
	int tmp = printf("* Before setting ");
	printntime("*", LEN - tmp);
	printf("\n");
	fflush(stdout);
	nb_err += check_print_int_array("tab1", tab1, 6, 18);

	// Settings
	for (int i = 0; i < 6; i++)
		tab1[i] = i;
	
	// Print After setting
	tmp = printf("* After setting ");
	printntime("*", LEN - tmp);
	printf("\n");
	fflush(stdout);
	nb_err += check_print_int_array("tab1", tab1, -2, 6);
	nb_err += check_print_int_array("tab1", tab1, 0, 6);
	nb_err += check_print_int_array("tab1", tab1, 5, 15);
	nb_err += check_print_int_array("tab1", tab1, 6, 18);
	//nb_err += check_print_int_array("tab1", tab1, 8, 24); //⚠️  Undefined Behavior
	
	// test ft_free_int_array() set tab1 at NULL
	psf = printf("ft_free_int_array(&tab1)-->free then set at NULL");
	ft_free_int_array(&tab1);
	printntime(S3, LEN - psf - 3);
	if (!tab1)
		psf += printf(PASS);
	else
	{
		psf += printf(FAIL);
		nb_err++;
	}
	psf = 0;
	print_sep(S2);
	
	// -[  ]--------------------------------------------------------------------
	print_subtitle("B.2| size=6, then set to [1, 10, 100, 1000, 10000, 100000]:");
	psf = printf("tab2 = ft_init_int_array(0) <=> [0, 0, 0, 0, 0, 0]");
	fflush(stdout);
	int	*tab2 = ft_init_int_array(6);
	printntime(S3, LEN - psf - 3);
	if (tab2)
		psf += printf(PASS);
	else
	{
		psf += printf(FAIL);
		nb_err++;
	}

	// Print Before setting
	tmp = printf("* Before setting ");
	printntime("*", LEN - tmp);
	printf("\n");
	fflush(stdout);
	nb_err += check_print_int_array("tab2", tab2, 6, 18);

	// Setting
	for (int i = 0; i < 6; i++)
	{
		tab2[i] = 1;
		for (int j = 0; j < i; j++)
			tab2[i] *= 10;
	}
	
	// Print After setting
	tmp = printf("* After setting ");
	printntime("*", LEN - tmp);
	printf("\n");
	fflush(stdout);
	nb_err += check_print_int_array("tab2", tab2, -2, 6);
	nb_err += check_print_int_array("tab2", tab2, 0, 6);
	nb_err += check_print_int_array("tab2", tab2, 5, 25);
	nb_err += check_print_int_array("tab2", tab2, 6, 33);
	//nb_err += check_print_int_array("tab2", tab2, 8, 39); //⚠️  Undefined Behavior
	
	// test ft_free_int_array() set tab2 at NULL
	psf = printf("ft_free_int_array(&tab2)-->free then set at NULL");
	ft_free_int_array(&tab2);
	printntime(S3, LEN - psf - 3);
	if (!tab2)
		psf += printf(PASS);
	else
	{
		psf += printf(FAIL);
		nb_err++;
	}
	psf = 0;
	print_sep(S2);
	
// =[  ]========================================================================
	fflush(stdout);
	close(fd);
	if (!is_a_file(ft))
		return (fprintf(stderr, "ERROR:\"%s\" Not created\n%s", ft, USAGE), free(ft), free(real), 1);
	nb_err += compare_files(ft,real);
	return (free(ft), free(real), nb_err);
}
