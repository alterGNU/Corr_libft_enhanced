#include "libft.h"
#include <string.h> // bzero
#include <stdio.h>  // printf

int	compare_str(char *s1, char *s2, size_t n)
{
	int	nb_err = 0;
	char *old_s1=strdup(s1);
	if (!old_s1)
		return (0);
	char *old_s2=strdup(s2);
	if (!old_s2)
	{
		free(old_s1);
		return (0);
	}
	size_t	len_s1 = strlen(s1);
	size_t	len_s2 = strlen(s2);
	printf("\nbzero(\"%s\", \"%s\", %ld)\n",s1,s2,n);
	bzero(s1, n);
	ft_bzero(s2, n);
    printf("s1:\"");
	for (size_t i=0;i<len_s1;i++)
    {
        (s1[i]) ? printf("%c",s1[i]) : printf("\\0") ;
		if ((i < n && s1[i]) || (i >=n && s1[i] != old_s1[i]))
			nb_err++;
    }
    printf("\"\n");
    printf("s2:\"");
	for (size_t i=0;i<len_s2;i++)
    {
        (s2[i]) ? printf("%c",s2[i]) : printf("\\0") ;
		if ((i < n && s2[i]) || (i >=n && s2[i] != old_s2[i]))
			nb_err++;
    }
    printf("\"\n");
	free(old_s1);
	free(old_s2);
	return ((nb_err)?1:0);
}

// =[ INT ARRAY TEST ]==========================================================
void	print_tab(int *tab, int size)
{
	printf("[");
	for(int i=0;i<size;i++)
	{
		printf("%d",tab[i]);
		if (i + 1 < size)
			printf(", ");
	}
	printf("]\n");
}

int	compare_tab(int *t1, int *t2, int tab_size, int size)
{
	int	nb_err = 0;
	printf("\nbzero(tab, %d)\n", size);
	printf("-AVANT:\n");
	print_tab(t1,tab_size);
	print_tab(t2,tab_size);
	bzero(t1, sizeof(int) * size);
	ft_bzero(t2, sizeof(int) * size);
	printf("-APRES:\n");
	print_tab(t1,tab_size);
	print_tab(t2,tab_size);
	for (int i=0;i<size;i++)
		if (t1[i] != t2[i])
			nb_err++;
	return ((nb_err)?1:0);
}

int	main()
{
	int	tot_fail=0;
// -[ 	COMPARE STRING ]---------------------------------------------------------
    printf("\nTEST SUR CHAINES DE CARACTERES:\n");
    char sa0[16];
    char sb0[16];
    strcpy(sa0, "");
    strcpy(sb0, "");
    tot_fail+=compare_str(sa0, sb0, 0);

    char sa1[16];
    char sb1[16];
    strcpy(sa1, "Coucou.");
    strcpy(sb1, "Coucou.");
    tot_fail+=compare_str(sa1, sb1, 0);
    strcpy(sa1, "Coucou.");
    strcpy(sb1, "Coucou.");
    tot_fail+=compare_str(sa1, sb1, 4);
    strcpy(sa1, "Coucou.");
    strcpy(sb1, "Coucou.");
    tot_fail+=compare_str(sa1, sb1, 7);

// -[ 	COMPARE TABLEAUX ENTIERS ]-----------------------------------------------
    printf("\nTEST SUR TABLEAUX d'ENTIERS:\n");
	int	t0[0] = {};
	int	T0[0] = {};
	tot_fail+=compare_tab(t0, T0, 0, 0);

	int	t1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	T1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (int i=0;i<=9;i++)
		tot_fail+=compare_tab(t1, T1, 9, i);

	return (tot_fail);
}
