#include "libft.h"
#include <bsd/string.h> // strlcpy
#include <stdio.h>      // printf

int	compare_str(const char *src, char *d1,  char *d2, size_t n)
{
	size_t	real;
	size_t	ft;
	size_t	size = strlen(src);
	real = strlcpy(d1, src, n);
	ft = ft_strlcpy(d2, src, n);
	printf("real:%ld vs ft:%ld\n",real,ft);
	if (real != ft)
		return (1);
	for(size_t i=0;i<size;i++)
	{
		if ((i + 1 < n ) && ( d1[i] != d2[i] || d1[i] != src[i]) )
			return (1);
		if ((i + 1 == n ) && (d1[i] || d2[i]) )
			return (1);
		if (i + 1 > n  && d1[i] != d2[i] )
			return (1);
	}
	return (0);
}

int	main()
{
	int	nb_err=0;

	// CAS SOURCE ET DESTINATION VIDE
    char *s0="";
    char *d0=(char *) calloc(strlen(s0)+1, sizeof(char));
	if (!d0)
		return (404);
    char *D0=(char *) calloc(strlen(s0)+1, sizeof(char));
	if (!D0)
	{
		free(d0);
		return (404);
	}
    nb_err+=compare_str(s0, d0, D0, 0);
	memset(d0,0,strlen(s0));
	memset(D0,0,strlen(s0));
    nb_err+=compare_str(s0, d0, D0, 1);
	free(d0);
	free(D0);
	
	// CAS CLASSIC
    const char *s1="abcdedfg";
	for (int i = -1; i<9; i++)
    {
		char *d1=strdup("123456789");
		if(!d1)
			return (404);
		char *D1=strdup("123456789");
		if(!D1)
		{
			free(d1);
			return (404);
		}
		printf("\nd1:\"%s\"\nD1:\"%s\"\n",d1,D1);
		printf("strlcpy(d1:\"%s\",s1:\"%s\", %d)\n",d1,s1,i);
		printf("ft_strlcpy(D1:\"%s\",s1:\"%s\", %d)\n",D1,s1,i);
		nb_err+=compare_str(s1, d1, D1, i);
		printf("d1:\"%s\"\nD1:\"%s\"\n",d1,D1);
		free(d1);
		free(D1);
    }

	printf("%d fin\n",nb_err);
	return (nb_err);
}
