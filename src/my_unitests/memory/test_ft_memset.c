#include "libft.h"
#include <string.h> // memset
#include <stdio.h>  // printf

int	compare_str(char *s1, char *s2, int c, size_t n)
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
	printf("\nmemset(\"%s\", \"%s\", %c, %ld)\n",s1,s2,c,n);
	printf("-AVANT:\n\t-s1=\"%s\"\n\t-s2=\"%s\"\n",s1,s2);
	memset(s1, c, n);
	ft_memset(s2, c, n);
	printf("-APRES:\n\t-s1=\"%s\"\n\t-s2=\"%s\"\n",s1,s2);
	for (size_t i=0;i<len_s1;i++)
		if ((i < n && s1[i] != c) || (i >=n && s1[i] != old_s1[i]))
			nb_err++;
	for (size_t i=0;i<len_s2;i++)
		if ((i < n && s2[i] != c) || (i >=n && s2[i] != old_s2[i]))
			nb_err++;
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

int	compare_tab(int *t1, int *t2, int tab_size, int size, int value)
{
	int	nb_err = 0;
	printf("\nmemset(tab, %c, %d)\n", value, size);
	printf("-AVANT:\n");
	print_tab(t1,tab_size);
	print_tab(t2,tab_size);
	memset(t1, value, sizeof(int) * size);
	ft_memset(t2, value, sizeof(int) * size);
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
    printf("\nTEST SUR CHAINES DE CARACTERES\n:");
    char sa0[16];
    char sb0[16];
    strcpy(sa0, "");
    strcpy(sb0, "");
    tot_fail+=compare_str(sa0, sb0, '*', 0);

    char sa1[16];
    char sb1[16];
    strcpy(sa1, "Coucou.");
    strcpy(sb1, "Coucou.");
    tot_fail+=compare_str(sa1, sb1, '*', 0);
    strcpy(sa1, "Coucou.");
    strcpy(sb1, "Coucou.");
    tot_fail+=compare_str(sa1, sb1, '*', 4);
    strcpy(sa1, "Coucou.");
    strcpy(sb1, "Coucou.");
    tot_fail+=compare_str(sa1, sb1, '*', 7);

// -[ 	COMPARE TABLEAUX ENTIERS ]-----------------------------------------------
    printf("\nTEST SUR TABLEAUX d'ENTIERS\n:");
	int	t0[0] = {};
	int	T0[0] = {};
	tot_fail+=compare_tab(t0, T0, 0, 0, 0);

	int	t1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	T1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (int i=0;i<=9;i++)
		tot_fail+=compare_tab(t1, T1, 9, i, 0);

	return (tot_fail);
}
