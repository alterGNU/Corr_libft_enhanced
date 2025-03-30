#include "libft.h"
#include <string.h> // memmove
#include <stdio.h>  // printf

#define BUFF 32

// =[ STR TEST ]================================================================
int	compare_str(char *d1, char *s1, char *d2, char *s2, size_t n)
{
	printf("\ndst1:\"%s\"\ndst2:\"%s\"\n",d1,d2);
	printf("memmove(dst1:\"%s\",src1:\"%s\", %ld)\n",d1,s1,n);
	printf("ft_memmove(dst2:\"%s\",src2:\"%s\", %ld)\n",d2,s2,n);
	memmove(d1, s1, n);
	ft_memmove(d2, s2, n);
	printf("dst1:\"%s\"\ndst2:\"%s\"\n",d1,d2);
	return (strcmp(d1,d2));
}

int	main()
{
	int	nb_err=0;
// -[ 	COMPARE STRING ]---------------------------------------------------------
    printf("\nTEST SUR CHAINES DE CARACTERES:\n");
	// CAS SOURCE ET DESTINATION VIDE
    printf("\nCAS SOURCE ET DESTINATION VIDE:\n");
    char s0[BUFF]="";
    char S0[BUFF]="";
    char d0[BUFF]="";
    char D0[BUFF]="";
    nb_err+=compare_str(d0, s0, D0, S0, 0);
    nb_err+=compare_str(d0, s0, D0, S0, 5);
	// CAS PAS DE CHEVAUCHEMENT [ dst ] ( src )
    printf("\nCAS PAS DE CHEVAUCHEMENT [ dst ] ( src ):\n");
    char s1[BUFF]="coucou petite perruche";
    char S1[BUFF]="coucou petite perruche";
    char d1[BUFF]="";
    char D1[BUFF]="";
    nb_err+=compare_str(d1, s1, D1, S1, 0);
    nb_err+=compare_str(d1, s1, D1, S1, 23);
	// CAS CHEVAUCHEMENT TOTAL [( dst src )]
    printf("\nCAS CHEVAUCHEMENT TOTAL [( dst src )]:\n");
    nb_err+=compare_str(s1, s1, S1, S1, 23);
	// CAS CHEVAUCHEMENT [ dst ( ] src )
    printf("\nCAS CHEVAUCHEMENT [ dst ( ] src ):\n");
    char s2[BUFF]="0123456789";
    char S2[BUFF]="0123456789";
    nb_err+=compare_str(s2, s2+3, S2, S2+3, 5);
	// CAS CHEVAUCHEMENT ( src [ ) dst ]
    printf("\nCAS CHEVAUCHEMENT ( src [ ) dst ]:\n");
    char s3[BUFF]="0123456789";
    char S3[BUFF]="0123456789";
    nb_err+=compare_str(s3+3, s3, S3+3, S3, 5);

	return (nb_err);
}
