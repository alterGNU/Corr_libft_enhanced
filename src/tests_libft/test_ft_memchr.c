#include "libft.h"  // ft_memchr
#include <string.h> // memchr
#include <stdio.h>  // printf

int	compare_str(const char *str, int c, size_t n)
{
	printf("\n(ft_)memchr(\"%s\", %c, %ld)\n", str, c, n);
	char *real = memchr(str, c, n);
	char *ft = ft_memchr(str, c, n);
	printf("real=\"%s\"\nft  =\"%s\"\n", real, ft);
	int	r = (real != ft);
	printf(r ?"\t\t\t----> FAIL!\n" : "\t\t\t----> PASS!\n");
	return (r);
}

int	main()
{
	int	nb_err = 0;
	
	// CAS str="", c='a'
	printf("\t- CAS str=\"\", c='a'\n");
	for (int i=0;i<2;i++)
		nb_err+=compare_str("", 'a', i);
	
	// CAS str="", c=0
	printf("\t- CAS str=\"\", c='\\0'\n");
	for (int i=0;i<2;i++)
		nb_err+=compare_str("", 0 , i);
	
	// CAS str="abc", c=0
	printf("\t- CAS str=\"\", c='\\0'\n");
	for (int i=0;i<4;i++)
		nb_err+=compare_str("abc", 0 , i);
	
	// CAS str="abc", c='c'
	printf("\t- CAS str=\"\", c='b'\n");
	for (int i=0;i<4;i++)
		nb_err+=compare_str("abc", 'b' , i);
	
	// CAS str="abc", c='z'
	printf("\t- CAS str=\"\", c='z'\n");
	for (int i=0;i<4;i++)
		nb_err+=compare_str("abc", 'z' , i);
	
	return (nb_err);
}
