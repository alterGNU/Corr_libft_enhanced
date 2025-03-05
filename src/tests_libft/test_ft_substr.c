#include "libft.h"
#include <string.h> // strcomp
#include <stdio.h>  // printf, fprintf

int	test(char *src, unsigned int start, size_t len, char *res)
{
	printf("ft_substr(\"%s\", %d, %ld)\n",src,start,len);
	char *ft_res = ft_substr(src, start, len);
	if (!ft_res)
		return (0);
	if (!src)
	{
		printf("src=(null) et ");
		if (!ft_res)
		{
			printf("ft_res=\"%s\"----> PASS\n", ft_res);
			return (0);
		}
		printf("ft_res=\"%s\" ----> FAIL\n", ft_res);
		return (1);
	}
	printf("res:\"%s\" vs ft_res:\"%s\"",res, ft_res);
	int r = strcmp(res,ft_res);
	printf(r ? "----> FAIL\n\n" : "----> PASS\n\n");
	free(ft_res);
	return (r);
}

int	main()
{
	int	tot_fail=0;

	char	*s0 = NULL;
    printf("\n\t- CAS source NULL:\n");
	tot_fail+=test(s0, 1, 1, "");
    printf("\n\t- CAS source vide:\n");
	tot_fail+=test("", 0, -1, "");
	tot_fail+=test("", 0, 0, "");
	tot_fail+=test("", 0, 1, "");
    printf("\n\t- CAS len > strlen():\n");
	for(int i=5;i<11;i++)
		for(int j=0;j<6;j++)
			tot_fail+=test("slt !", i, j, "");

    printf("\n    - CAS source non vide:\n");
	tot_fail+=test("slt !", 0, -1, "slt !");
	tot_fail+=test("slt !", 0, 0, "");
	tot_fail+=test("slt !", 0, 1, "s");
	tot_fail+=test("slt !", 0, 2, "sl");
	tot_fail+=test("slt !", 0, 3, "slt");
	tot_fail+=test("slt !", 0, 4, "slt ");
	tot_fail+=test("slt !", 0, 5, "slt !");
	tot_fail+=test("slt !", 0, 6, "slt !");

	tot_fail+=test("slt !", 1, -1, "lt !");
	tot_fail+=test("slt !", 1, 0, "");
	tot_fail+=test("slt !", 1, 1, "l");
	tot_fail+=test("slt !", 1, 2, "lt");
	tot_fail+=test("slt !", 1, 3, "lt ");
	tot_fail+=test("slt !", 1, 4, "lt !");
	tot_fail+=test("slt !", 1, 5, "lt !");
	tot_fail+=test("slt !", 1, 6, "lt !");

	tot_fail+=test("slt !", 2, 0, "");
	tot_fail+=test("slt !", 2, 1, "t");
	tot_fail+=test("slt !", 2, 2, "t ");
	tot_fail+=test("slt !", 2, 3, "t !");
	tot_fail+=test("slt !", 2, 4, "t !");

	tot_fail+=test("slt !", 3, 0, "");
	tot_fail+=test("slt !", 3, 1, " ");
	tot_fail+=test("slt !", 3, 2, " !");
	tot_fail+=test("slt !", 3, 3, " !");

	tot_fail+=test("slt !", 4, 0, "");

	for (int i = 1; i<7; i++)
		tot_fail+=test("slt !", 4, i, "!");

    printf("\n\t- CAS particuliers start hors size source:\n");
	for (int i = 0; i<7; i++)
		tot_fail+=test("slt !", 5, i, "");

	return (tot_fail);
}
