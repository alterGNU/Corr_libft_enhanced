#include "libft.h"  // ft_strcspn
#include <string.h> // strcspn
#include <stdio.h>  // printf
#define LEN 100

int	printntime(char c, int n)
{
	for (int i = 0 ; i < n; i++)
		printf("%c", c);
	return (n);
}

void print_title(const char *title)
{
	int print_sofar = printf("=[ %s ]", title);
	printntime('=', LEN - print_sofar);
	printf("\n");
}

int	test(char *src, char *reject)
{
	int	print_sofar;
	int	ft;
	int	real;
	ft = ft_strcspn(src, reject);
	if (!src || !reject)
	{
		print_sofar=printf("strcspn(\"%s\", \"%s\")ft-> [%d]", src, reject, ft);
		if (ft == -1)
			return (printntime('-', LEN-print_sofar-7), printf("> ✅\n"), 0);
		return (printntime('-', LEN-print_sofar-7), printf("> ❌\n"), 1);
	}
	real = (int)strcspn(src, reject);
	print_sofar=printf("strcspn(\"%s\", \"%s\")[%d] vs [%d]", src, reject, real, ft);
	if (real == ft)
		return (printntime('-', LEN-print_sofar-7), printf("> ✅\n"), 0);
	return (printntime('-', LEN-print_sofar-7), printf("> ❌\n"), 1);
}

int main()
{
	int	nb_err = 0;
	print_title("ERRORS/NULL CASES (-1)");
	nb_err += test(NULL, NULL);
	nb_err += test("coucou ", NULL);
	nb_err += test(NULL, " ");
	print_title("CLASSIC");
	nb_err += test("", "");
	nb_err += test("abcdefghijklmopqrstuvwxyz", "");
	nb_err += test("coucou", "");
	nb_err += test("    c", " ");
	nb_err += test("    c", "c");
	nb_err += test("coucou", "c");
	nb_err += test("av1sd2cw34", "0123456789");
	nb_err += test("clkx1lxka34", "0123456789");
	nb_err += test("coucou ", "x ");
	char	src1[10]="123123123";
	char	src2[10]="12312312 ";
	for (int i = 0; i < 10; i++)
	{
		nb_err += test(src1+i, "asd345");
		nb_err += test(src2+i, " ");
	}
	nb_err += test("cat < file1 | cat >> file 2 && echo toto||echo titi;", ";");
	nb_err += test("cat < file1 | cat >> file 2 && echo toto||echo titi;", "<");
	nb_err += test("cat < file1 | cat >> file 2 && echo toto||echo titi;", "|");
	nb_err += test("cat < file1 | cat >> file 2 && echo toto||echo titi;", "||");
	nb_err += test("cat < file1 | cat >> file 2 && echo toto||echo titi;", ">");
	nb_err += test("cat < file1 | cat >> file 2 && echo toto||echo titi;", ">>");
	nb_err += test("cat < file1 | cat >> file 2 && echo toto||echo titi;", "&");
	nb_err += test("cat < file1 | cat >> file 2 && echo toto||echo titi;", "&&");
	nb_err += test("cat < file1 | cat >> file 2 && echo toto||echo titi;", ";<>|&");
	print_title("REPETITION");
	nb_err += test("...aa......aa", "a");
	nb_err += test("lskdjfblksjdbbbslkx", "bb");
	print_title("SPECIAL CHAR");
	nb_err += test("!@#' ", "'");
	nb_err += test("\"!@#<><<>>||&&&&", "\"");
	print_title("PERFORMANCES");
	nb_err += test("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	nb_err += test("aaaaaaaaaaaaaaaaaaaaaaaabcdefghijklmnopqrstuvwxyzAAAAAAAAAAAABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	return (nb_err);
}

