#include "libft.h"  // ft_strspn
#include <string.h> // strspn
#include <stdio.h>  // printf
#define LEN 100

int	printntime(char c, int n)
{
	for (int i = 0 ; i < n; i++)
		printf("%c", c);
	return (n);
}

int	test(char *src, char *accept)
{
	int	print_sofar;
	int	ft;
	int	real;
	ft = ft_strspn(src, accept);
	if (!src || !accept)
	{
		print_sofar=printf("strspn(\"%s\", \"%s\")ft-> [%d]", src, accept, ft);
		if (ft == -1)
			return (printntime('-', LEN-print_sofar-7), printf("> ✅\n"), 0);
		return (printntime('-', LEN-print_sofar-7), printf("> ❌\n"), 0);
	}
	real = (int)strspn(src, accept);
	print_sofar=printf("strspn(\"%s\", \"%s\")[%d] vs [%d]", src, accept, real, ft);
	if (real == ft)
		return (printntime('-', LEN-print_sofar-7), printf("> ✅\n"), 0);
	return (printntime('-', LEN-print_sofar-7), printf("> ❌\n"), 0);
}

int main()
{
	int	nb_err = 0;
	nb_err += test(NULL, NULL);
	nb_err += test("coucou ", NULL);
	nb_err += test(NULL, " ");

	nb_err += test("", "");
	nb_err += test("", "abcdefghijklmopqrstuvwxyz");
	nb_err += test("coucou", "");
	nb_err += test("     ", " ");
	nb_err += test("     ", "c");
	nb_err += test("coucou", "c");
	nb_err += test("1234", "0123456789");
	nb_err += test("12a34", "0123456789");
	nb_err += test("coucou ", "cou");

	char	src1[10]="123123123";
	char	src2[10]="12312312 ";
	for (int i = 0; i < 10; i++)
	{
		nb_err += test(src1+i, "12345");
		nb_err += test(src2+i, "12345");
	}
	return (nb_err);
}
