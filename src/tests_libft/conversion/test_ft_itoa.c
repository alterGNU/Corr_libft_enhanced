#include "libft.h"
#include <string.h> // strcmp
#include <stdio.h>  // printf, fprintf
#include <limits.h> // INT_MAX et INT_MIN

int	test(int n, const char *rpz)
{
	char *ft_res=ft_itoa(n);
	if (!ft_res)
		return (0);
	printf("ft_itoa(%d) real=\"%s\" VS ft=\"%s\"\t",n,rpz,ft_res);
	int r = strcmp(ft_res, rpz);
	free(ft_res);
	printf((r)?"---> FAIL\n":"---> PASS\n");
	return (r);
}

int	main()
{
	int tot_fail = 0;
	tot_fail += test(INT_MIN, "-2147483648");
	tot_fail += test(-12345, "-12345");
	tot_fail += test(-1234, "-1234");
	tot_fail += test(-123, "-123");
	tot_fail += test(-100, "-100");
	tot_fail += test(-12, "-12");
	tot_fail += test(-10, "-10");
	tot_fail += test(-5, "-5");
	tot_fail += test(0, "0");
	tot_fail += test(5, "5");
	tot_fail += test(10, "10");
	tot_fail += test(12, "12");
	tot_fail += test(100, "100");
	tot_fail += test(123, "123");
	tot_fail += test(1234, "1234");
	tot_fail += test(12345, "12345");
	tot_fail += test(INT_MAX, "2147483647");
	return (tot_fail);
}
