#include "libft.h"  //ft_strncmp
#include <string.h> // strncmp
#include <stdio.h>  // printf

#define f_name "strncmp"

int	compare(const char *s1, const char *s2, size_t n)
{
	int	    real;
	int	    ft;

	real = strncmp(s1, s2, n);
	ft = ft_strncmp(s1, s2, n);
	printf("strncmp(\"%s\", \"%s\", %ld) = real->[%d] == ft->[%d]\t",s1,s2,n,real,ft);
	//int	r = (real == ft);
	int	r = (!real == !ft);
	printf(r?"--------> PASS!\n" : "--------> FAIL!\n");
	return (!r);
}

int	main()
{
	int nb_err = 0;

	nb_err += compare("", "", 0);
	nb_err += compare("", "", 1);
	nb_err += compare("abcde", "", 0);
	nb_err += compare("abcde", "\0", 1);
	nb_err += compare("", "abcde", 0);
	nb_err += compare("", "abcde", 1);
	
	char	s1[6] = {'a','b','c','d','e','\0'};
	char	s2[6] = {'a','b','c','d','\0','\0'};
	for (int i=0;i<5;i++)
	{
		nb_err += compare(s1, "abcde", i);
		nb_err += compare(s2, "abcde", i);
		nb_err += compare("abcDE", s1, i);
	}

	return (nb_err);
}
