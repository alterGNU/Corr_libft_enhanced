#include "libft.h"  //ft_memcmp
#include <string.h> // memcmp
#include <stdio.h>  // printf

int	compare_str(const char *s1, const char *s2, size_t n)
{
	int	    real;
	int	    ft;

	real = memcmp(s1, s2, n);
	ft = ft_memcmp(s1, s2, n);
	printf("memcmp(\"%s\", \"%s\", %ld) = [%d] == [%d]",s1,s2,n,real,ft);
	int r = (real != ft);
	printf(r?"\t-----> FAIL!\n" : "\t-----> PASS!\n");
	return (r);
}

int	main()
{
	int	nb_err = 0;
	
	// CAS s1=s2=""
	printf("\nCAS s1=s2=\"\"\n");
	for (int i=0;i<2;i++)
		nb_err+=compare_str("", "", i);
	
	// CAS s1="" et s2="toto"
	printf("\nCAS s1=\"\" et s2=\"toto\"\n");
	for (int i=0;i<2;i++)
		nb_err+=compare_str("\0\0\0\0", "toto", i);
	
	// CAS s1="toto" et s2="toto"
	printf("\nCAS s1=\"toto\" et s2=\"toto\"\n");
	for (int i=0;i<6;i++)
		nb_err+=compare_str("toto", "toto", i);
	
	// CAS s1="tofu" et s2="toto"
	printf("\nCAS s1=\"totu\" et s2=\"toto\"\n");
	for (int i=0;i<4;i++)
		nb_err+=compare_str("totu", "toto", i);
	
	// CAS s1="to" et s2="toto"
	printf("\nCAS s1=\"to\" et s2=\"toto\"\n");
	for (int i=0;i<4;i++)
		nb_err+=compare_str("to", "toto", i);
	
	// CAS s1="toto" et s2="to"
	printf("\nCAS s1=\"toto\" et s2=\"to\"\n");
	for (int i=0;i<4;i++)
		nb_err+=compare_str("toto", "to", i);
	
	// CAS s1="toto" et s2="to"
	printf("\nCAS s1=\"t\" et s2=\"o\"\n");
	for (int i=0;i<2;i++)
		nb_err+=compare_str("t", "o", i);
	
	return (nb_err);
}
