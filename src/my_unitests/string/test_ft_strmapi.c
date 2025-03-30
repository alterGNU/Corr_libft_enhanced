#include "libft.h"
#include <string.h> // strcomp
#include <ctype.h>  // isupper
#include <stdio.h>  // printf

int	test(const char *str, char (*f)(unsigned int, char), char *res)
{
	printf("ft_strmapi(\"%s\", fct) devrait retourner \"%s\"\n",str , res);
	char *ft_res = ft_strmapi(str, f);
	if (!ft_res)
		return (0);
	printf("res:\"%s\" vs ft_res:\"%s\"",res, ft_res);
	int r = (!str || !f)?(int)(res!=NULL):strcmp(res,ft_res);
	printf((r)?"----> FAIL\n\n":"----> PASS\n\n");
	free(ft_res);
	return (r);
}

static char	all_upper(unsigned int i, char c)
{
	return ((char)(i ? ft_toupper(c) : ft_toupper(c)));
}

static char	all_lower(unsigned int i, char c)
{
	return ((char)(i ? ft_tolower(c) : ft_tolower(c)));
}

static char	title(unsigned int i, char c)
{
	return ((char)(i ? ft_tolower(c) : ft_toupper(c)));
}

static char	reverse(unsigned int i, char c)
{
	(void) i;
	return ((char)( isupper(c) ? ft_tolower(c) : ft_toupper(c)));
}

int	main()
{
	int	tot_fail=0;

    printf("\n\t- CAS s et/ou fct NULL:\n");
	char	*s0 = NULL;
	char	(*f0)(unsigned int, char) = NULL;
	tot_fail+=test(s0, all_upper, NULL);
	tot_fail+=test("blabla", f0, NULL);
	tot_fail+=test(s0, f0, NULL);

    printf("\n\t- CAS source et/ou set vides:\n");
	tot_fail+=test("", all_upper, "");
	tot_fail+=test("", all_lower, "");

    printf("\n    - CAS source et set non vides:\n");
	tot_fail+=test("Hello World!", all_lower, "hello world!");
	tot_fail+=test("Hello World!", all_upper, "HELLO WORLD!");
	tot_fail+=test("heLLo WORLD!", title, "Hello world!");
	tot_fail+=test("Hello World!", reverse, "hELLO wORLD!");
	tot_fail+=test("42", all_lower, "42");
	tot_fail+=test("42", all_upper, "42");
	tot_fail+=test("42", title, "42");
	tot_fail+=test("42", reverse, "42");

	return (tot_fail);
}
