#include "libft.h"
#include <ctype.h> // isspace()
#include <stdio.h> // printf

int	compare(int c)
{
	int	    real;
	int	    ft;

	real = isspace(c);
	ft = ft_isspace(c);
	printf("isspace(%c) = real[%d] == ft[%d]",c ,real ,ft); 
	if ((!real && ft) || (real && !ft))
	{
		printf("----> FAIL;"); 
		printf("\tERROR : isspace(%c) = real[%d] != ft[%d] ---> FAIL\n",c ,real ,ft); 
		return (1);
	}
	printf("---->PASS!\n"); 
	return (0);
}

int	main()
{
	int	tot_fail=0;
	for(int i=-200; i<200; i++)
		tot_fail+=compare(i);
	return (tot_fail);
}
