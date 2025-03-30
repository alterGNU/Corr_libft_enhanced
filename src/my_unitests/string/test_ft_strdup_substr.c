#include "libft.h"  // ft_strdup_substr()
#include <string.h> // strcmp()
#include <stdio.h>  // printf()

#define LEN 90
#define f_name "ft_strdup_substr"

int	printntime(char c, int n)
{
	for (int i = 0 ; i < n; i++)
		printf("%c", c);
	return (n);
	fflush(stdout);
}

int	count_char_in_str(char c, char *str)
{
	int	res;

	res = 0;
	while(*str)
	{
		if (*str == c)
			res++;
		str++;
	}
	return (res);
}

void print_title(const char *title)
{
	int print_sofar = printf("=[ %s ]", title);
	printntime('=', LEN - print_sofar + 1);
	printf("\n");
	fflush(stdout);
}

int	test(char *str, int start, int stop, char *res)
{
	int print_sofar = printf("%s(<%s>, %d, %d)==<%s>", f_name, str, start, stop, res);
	printntime('-', LEN - print_sofar - 3);
	char *ft = ft_strdup_substr(str, start, stop);
	if (!res || !ft)
	{
		if (!ft && !res)
			return (printf("> ✅\n"), 0);
		return (printf("---\n - res\t= <%s>\n - ft\t= <%s>\n", res, ft), ft_free((void **)&ft), printntime('-', LEN - 3), printf("> ❌\n"), 1);
	}
	if (!strcmp(ft, res))
		return (ft_free((void **)&ft), printf("> ✅\n"), 0);
	return (printf("---\n - res\t= <%s>\n - ft\t= <%s>\n", res, ft), ft_free((void **)&ft), printntime('-', LEN - 3), printf("> ❌\n"), 1);
}

int main()
{
	int	nb_err = 0;

	print_title("CAS:NULL");
	nb_err += test(NULL, 0, 1, NULL);   // INVALID arg:str null
	nb_err += test("hi", -1, 1, NULL);  // INVALID arg:start<0
	nb_err += test("hi", 2, 1, NULL);   // INVALID arg:start=='\0'
	nb_err += test("", 0, 1, NULL);     // INVALID arg:start=='\0'
	nb_err += test("", 0, 0, NULL);     // INVALID arg:start==stop=='\0'
	nb_err += test("hi", 0, -1, NULL);  // INVALID arg:stop<0
	nb_err += test("hi", 0, 0, NULL);   // INVALID arg:start==stop
	nb_err += test("hi", 1, 1, NULL);   // INVALID arg:start==stop
	nb_err += test("hi", 2, 2, NULL);   // INVALID arg:start==stop
	nb_err += test("hello", 3, 2, NULL);// INVALID arg:start>stop

	print_title("CAS:Classic");
	nb_err += test("hello world", 0, 11, "hello world");
	nb_err += test("hello world", 1, 10, "ello worl");
	nb_err += test("hello world", 2, 9, "llo wor");
	nb_err += test("hello world", 3, 8, "lo wo");
	nb_err += test("hello world", 4, 7, "o w");
	nb_err += test("hello world", 5, 6, " ");

	print_title("CAS:Stop > strlen");
	nb_err += test("hello", 0, 7, "hello");
	nb_err += test("hello", 1, 6, "ello");
	nb_err += test("hello", 2, 5, "llo");

	return (nb_err);
}
