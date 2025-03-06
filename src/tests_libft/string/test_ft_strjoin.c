#include "libft.h"
#include <string.h> // strcomp
#include <stdio.h>  // printf, fprintf

int	test(char *s1, char *s2, char *res)
{
	printf("ft_strjoin(\"%s\", \"%s\")\n",s1,s2);
	char *ft_res = ft_strjoin(s1, s2);
	if (!ft_res)
		return (0);
	if (!s1 || !s2)
	{
		printf("CAS NULL: ");
		if (ft_res)
		{
			printf("ft_res = \"%s\" instead of (null) ----> FAIL\n\n", ft_res);
			free(ft_res);
			return (1);
		}
		else
		{
			printf("ft_res = \"%s\" ----> PASS\n\n", ft_res);
			return (0);
		}
	}
	printf("res:\"%s\" vs ft_res:\"%s\"",res, ft_res);
	int r = (strcmp(res,ft_res))?1:0;
	printf((strcmp(res,ft_res))?"----> FAIL\n\n":"----> PASS\n\n");
	free(ft_res);
	return (r);
}

int	main()
{
	int	tot_fail=0;

	char	*s1 = NULL;
	char	*s2 = NULL;
    printf("\n    - CAS s1 et/ou s2 NULL:\n");
	tot_fail+=test(s1, "salut", "peutimporteu");
	tot_fail+=test("salut", s2, "peutimporteu");
	tot_fail+=test(s1, s2, "peutimporteu");

    printf("\n    - CAS s1 et/ou s2 vide:\n");
	tot_fail+=test("", "", "");
	tot_fail+=test("", "abc", "abc");
	tot_fail+=test("abc", "", "abc");

    printf("\n    - CAS ou deux non vides:\n");
	tot_fail+=test("abc", "123", "abc123");
	tot_fail+=test("123", "abc", "123abc");

	return (tot_fail);
}
