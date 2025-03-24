#include "libft.h"
#include <string.h> // strlen()
#include <stdio.h>  // printf

#define f_name "strlen"

int	compare(char *str)
{
	size_t	real;
	size_t	ft;

	ft = ft_strlen(str);
	if (!str)
	{
		printf("strlen(%s) = real:UB, ft_strlen(%s)=%d",str , str, ft);
		if (ft == 0)
			return ( printf("----> PASS!\n") , 0);
		return ( printf("----> FAIL!\n") , 1);
	}
	real = strlen(str);
	printf("strlen(%s) = real[%ld] == ft[%ld]",str ,real ,ft); 
	if ((!real && ft) || (real && !ft))
	{
		printf("----> FAIL!"); 
		printf("\tERROR : strlen(%s) = real[%ld] != ft[%ld]\n",str ,real ,ft); 
		return (1);
	}
	printf("----> PASS!\n"); 
	return (0);
}

int	main()
{
	int	tot_fail=0;
	char s0[4] = {'\0','\0','\0','\0'} ;
	char s1[4] = {'\0','a','\0','\0'} ;
	char *list[7]={s0, s1, "", "\0",  "toto", "to\0to","\nle\tgras\tc'est\rla\tvie\nle GRAS\n"};
	for(int i=0;i<7;i++)
		tot_fail+=compare(list[i]);

	return (tot_fail);
}
