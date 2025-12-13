// =============================================================================
// TESTS PRINT_IF FUNCTION
// 
// This program calls ft_printif with various arguments combinations
//  - tests/log/<date>/<time>/ft_printif/ft_printif.txt
// This newly created file is then compared with the provide file:
//  - tests/src/my_unitests/docs/ft_printif.txt
// file that contains the expected outputs.
// If they're identical, the program returns 0, else it returns 1.
//
// - TESTED CASES (diff. args combinaisions):
//   - int	*ft_printif(test <0, str, ...) --> should ft==print(str, ...)
//   - int	*ft_printif(test==0, str, ...) --> should ft==not print
//   - int	*ft_printif(test >0, str, ...) --> should ft==print(str, ...)
// =============================================================================
 
// =[ INCLUDE ]=================================================================
#include "libft.h"    // ft_printif
                      // include <unistd.h> --> dup2
#include <string.h>   // strcmp
#include <stdio.h>    // printf, fflush
#include <fcntl.h>    // open, close
#include <sys/stat.h> // struct stat (use in is_a_{file, folder})
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "ft_printif"
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
		return (fclose(f1), perror("ERROR compare_file()->fopen(f2)"), 1);

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
	char *fname = strdup("/ft_printif.txt");
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

	int r_ft = 0;
	int	r_real = 0;
	int psf = 0;
	
    // -[ "A| test < 0, SHOULD PRINT" ]-----------------------------------------
	print_title("A| test < 0, SHOULD PRINT");

	char *null_str = NULL;
	print_subtitle("A.0| NULL str");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(-1, "%s", null_str);
	printf(">\nreal:<");
	r_real = printf("%s", null_str);
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_subtitle("A.1| empty str");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(-1, "%s","");
	printf(">\nreal:<");
	r_real = printf("%s","");
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_subtitle("A.2| str without args format");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(-1, "\tThis is a simple string");
	printf(">\nreal:<");
	r_real = printf("\tThis is a simple string");
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_subtitle("A.3| str with args format");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(-1, "%s is a char %c == %d, and a free() fun add.=%p", "This", 'c', 'c', (void *)0x12345678);
	printf(">\nreal:<");
	r_real = printf("%s is a char %c == %d, and a free() fun add.=%p", "This", 'c', 'c', (void *)0x12345678);
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_sep(S1);
	
    // -[ "B| test < 0, SHOULD PRINT" ]-----------------------------------------
	print_title("B| test == 0, SHOULD NOT PRINT");

	print_subtitle("B.0| NULL str");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(0, "%s", null_str);
	printf(">\nreal:<");
	r_real = 0;
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_subtitle("B.1| empty str");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(0, "%s","");
	printf(">\nreal:<");
	r_real = 0;
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_subtitle("B.2| str without args format");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(0, "\tThis is a simple string");
	printf(">\nreal:<");
	r_real = 0;
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_subtitle("B.3| str with args format");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(0, "%s is a char %c == %d, and a free() fun add.=%p", "This", 'c', 'c', (void *)0x12345678);
	printf(">\nreal:<");
	r_real = 0;
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_sep(S1);
	
    // -[ "C| test > 0, SHOULD PRINT" ]-----------------------------------------
	print_title("C| test > 0, SHOULD PRINT");

	print_subtitle("C.0| NULL str");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(42, "%s", null_str);
	printf(">\nreal:<");
	r_real = printf("%s", null_str);
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_subtitle("C.1| empty str");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(42, "%s","");
	printf(">\nreal:<");
	r_real = printf("%s","");
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_subtitle("C.2| str without args format");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(42, "\tThis is a simple string");
	printf(">\nreal:<");
	r_real = printf("\tThis is a simple string");
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);

	print_subtitle("C.3| str with args format");
	printf("ft  :<");
	fflush(stdout);
	r_ft = ft_printif(42, "%s is a char %c == %d, and a free() fun add.=%p", "This", 'c', 'c', (void *)0x12345678);
	printf(">\nreal:<");
	r_real = printf("%s is a char %c == %d, and a free() fun add.=%p", "This", 'c', 'c', (void *)0x12345678);
	printf(">\n");
	psf = printf("ft:[%d] == real:[%d]", r_ft, r_real);
	printntime(S3, LEN - psf - 3);
	if (r_ft == r_real)
		printf(PASS);
	else
	{
		nb_err++;
		printf(FAIL);
	}
	print_sep(S2);
	
	print_sep(S1);

	

// =[  ]========================================================================
	fflush(stdout);
	close(STDOUT_FILENO);  // Close the redirected stdout
	close(fd);
	if (!is_a_file(ft))
		return (fprintf(stderr, "ERROR:\"%s\" Not created\n%s", ft, USAGE), free(ft), free(real), 1);
	nb_err += compare_files(ft,real);
	return (free(ft), free(real), nb_err);
}
