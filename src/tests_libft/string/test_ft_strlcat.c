#include "libft.h"      // ft_strlcat
#include <bsd/string.h> // strlcat, strcmp
#include <stdio.h>      // printf

int	compare(char *d1, char *d2, const char *src, size_t n)
{
	size_t	real;
	size_t	ft;
	printf("\nstrlcat(\"%s\",\"%s\",%ld)\n",d1, src, n);
	printf("ft_strlcat(\"%s\",\"%s\",%ld)\n", d2, src, n);
	real=strlcat(d1, src, n);
	ft=ft_strlcat(d2, src, n);
	printf("real_dst\"%s\"\n",d1);
	printf("ft_dst  \"%s\"\n", d2);
	printf("real=%ld vs ft=%ld",real, ft);

	size_t s1 = strlen(d1);
	size_t s2 = strlen(d2);
	int r = (strcmp(d1, d2) && ((ft != real) || (s1 != s2))) ? 1 : 0;
	printf((r) ? "-------------> FAIL\n" : "-------------> PASS\n");
	return (r);
}

int	main()
{
	int	nb_err = 0;
	char real_dst[30];
	char ft_dst[30];

	printf("\nCAS: DST=VIDE SRC=VIDE ---------------------\n");
	memset(real_dst, 0, 30);
	memset(ft_dst, 0, 30);
	for (int i=-1;i<2;i++)
	{
		nb_err+=compare(real_dst, ft_dst, "", i);
		memset(real_dst, 0, 30);
		memset(ft_dst, 0, 30);
	}

	printf("\nCAS: DST=VIDE SRC=NON-VIDE ----------------\n");
	memset(real_dst, 0, 30);
	memset(ft_dst, 0, 30);
	for (int i=-1;i<6;i++)
	{
		nb_err+=compare(real_dst, ft_dst, "123", i);
		memset(real_dst, 0, 30);
		memset(ft_dst, 0, 30);
	}
	
	printf("\nCAS: DST=NON-VIDE SRC=NON-VIDE ------------\n");
	memset(real_dst, 'e', 5);
	memset(ft_dst, 'e', 5);
	for (int i=-1;i<9;i++)
	{
		nb_err+=compare(real_dst, ft_dst, "123", i);
		memset(real_dst, 'e', 5);
		memset(ft_dst, 'e', 5);
	}

	return (nb_err);
}
