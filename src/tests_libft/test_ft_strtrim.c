#include "libft.h"
#include <string.h> // strcomp
#include <stdio.h>  // printf

int	test(char *src, char *set, char *res)
{
	printf("ft_strtrim(\"%s\", \"%s\")\n",src,set);
	char *ft_res = ft_strtrim(src, set);
	if (!ft_res)
		return (0);
	if (!src || !set)
	{
		printf("src/ou/et/set NULL :");
		if (!ft_res)
		{
			printf("----> PASS\n\n");
			return (0);
		}
		printf("----> FAIL\n\n");
		return (1);
	}
	printf("res:\"%s\" vs ft_res:\"%s\"",res, ft_res);
	int r = strcmp(res,ft_res);
	printf((r)?"----> FAIL\n\n":"----> PASS\n\n");
	free(ft_res);
	return (r);
}

int	main()
{
	int	tot_fail=0;

    printf("\n\t- CAS source et/ou set NULL:\n");
	char	*s0 = NULL;
	tot_fail+=test(s0, "?", "peutimporteu");
	tot_fail+=test("blabla", s0, "blabla");
	tot_fail+=test(s0, s0, "peutimporteu");

    printf("\n\t- CAS source et/ou set vides:\n");
	tot_fail+=test("Hakuna matata", "", "Hakuna matata");
	tot_fail+=test("", "e", "");
	tot_fail+=test("", "", "");

    printf("\n    - CAS source et set non vides:\n");
	tot_fail+=test("   Coucou petite perruche   ", " ", "Coucou petite perruche");
	tot_fail+=test("sssCoucou petite perruchefff", "fs", "Coucou petite perruche");
	tot_fail+=test("sSsSsCoucou petite perruchefFfFf", "fFSs", "Coucou petite perruche");
	tot_fail+=test("sssCoucou petite perruchefff", "fsx", "Coucou petite perruche");
	tot_fail+=test("sSsSsCoucou petite perruchefFfFf", "fFSsxX", "Coucou petite perruche");
	tot_fail+=test("42", "42", "");
	tot_fail+=test("42424242", "42", "");
	tot_fail+=test("eseseeeee", "e", "ses");
	tot_fail+=test("\t\ttab\ttab\t\t", "\t", "tab\ttab");
	tot_fail+=test("....que debut", ".", "que debut");
	tot_fail+=test("que fin....", ".", "que fin");

	return (tot_fail);
}
