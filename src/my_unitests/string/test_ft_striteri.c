#include "libft.h"
#include <string.h> // strcomp
#include <ctype.h>  // isupper
#include <stdio.h>  // printf

int	test(char *str, void (*f)(unsigned int, char*), char *res)
{
	printf("ft_striteri(\"%s\", fct)\nAVANT\"%s\"\n",str , res);
	ft_striteri(str, f);
	printf("APRES\"%s\"\n",str);
	int r = (!str)?!(int)(str == res):strcmp(res,str);
	printf((r)?"----> FAIL\n\n":"----> PASS\n\n");
	return (r);
}

static void	ft_xtoupper(unsigned int i, char *c)
{
	(void) i;
	*c = (char)ft_toupper((unsigned char)(*c));
}

static void	ft_xtolower(unsigned int i, char *s)
{
	(void) i;
	*s = (char) ft_tolower((unsigned char)(*s));
}

static void	ft_xtitle(unsigned int i, char *s)
{
	*s = (char)(i ? ft_tolower((unsigned char)(*s)) : ft_toupper((unsigned char)(*s))) ;
}

static void	ft_xreverse(unsigned int i, char *s)
{
	(void) i;
	*s =  ((char)( isupper((unsigned char)(*s)) ? ft_tolower((unsigned char)(*s)) : ft_toupper((unsigned char)(*s))));
}

int	main()
{
	int	tot_fail=0;

    printf("\n\t- CAS s et/ou fct NULL:\n");
	char	*s0 = NULL;
	void	(*f0)(unsigned int, char*) = NULL;
	tot_fail+=test(s0, ft_xtoupper, NULL);
	tot_fail+=test("blabla", f0, "blabla");
	tot_fail+=test(s0, f0, NULL);

    printf("\n\t- CAS source et/ou set vides:\n");
	char	s1[]= "";
	tot_fail+=test(s1, ft_xtoupper, s1);
	tot_fail+=test(s1, ft_xtolower, s1);
	tot_fail+=test(s1, ft_xtitle, s1);
	tot_fail+=test(s1, ft_xreverse, s1);

    printf("\n    - CAS source et set non vides:\n");
	char	s2[]= "Hello World!";
	tot_fail+=test(s2, ft_xreverse, "hELLO wORLD!");
	tot_fail+=test(s2, ft_xtoupper, "HELLO WORLD!");
	tot_fail+=test(s2, ft_xtolower, "hello world!");
	tot_fail+=test(s2, ft_xtitle, "Hello world!");
	char	s3[]= "heLLo WORLD!";
	tot_fail+=test(s3, ft_xreverse, "HEllO world!");
	tot_fail+=test(s3, ft_xtoupper, "HELLO WORLD!");
	tot_fail+=test(s3, ft_xtolower, "hello world!");
	tot_fail+=test(s3, ft_xtitle, "Hello world!");
	char	s4[]= " heLLo WORLD!";
	tot_fail+=test(s4, ft_xreverse, " HEllO world!");
	tot_fail+=test(s4, ft_xtoupper, " HELLO WORLD!");
	tot_fail+=test(s4, ft_xtolower, " hello world!");
	tot_fail+=test(s4, ft_xtitle, " hello world!");
	char	s5[]= "42";
	tot_fail+=test(s5, ft_xreverse, "42");
	tot_fail+=test(s5, ft_xtoupper, "42");
	tot_fail+=test(s5, ft_xtolower, "42");
	tot_fail+=test(s5, ft_xtitle, "42");

	return (tot_fail);
}
