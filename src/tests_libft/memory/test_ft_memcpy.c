#include "libft.h"
#include <string.h> // memcpy, strcmp
#include <stdio.h>  // printf

// =[ STR TEST ]================================================================
int	compare_str(char *src, size_t n)
{
	int		nb_err = 0;
	if (!src)
	{
		printf("CAS source null et n==%ld\n", n);
		char	*dst1 = (char *) calloc(15, sizeof(char));
		if (!dst1)
			return (404);
		char 	*dst2 = (char *) calloc(15, sizeof(char));
		if (!dst2)
		{
			free(dst1);
			return (404);
		}
		memset(dst1, 'A', 15);
		memset(dst2, 'A', 15);
		printf("AVANT:dst1=\"%s\"\n", dst1);
		printf("AVANT:dst2=\"%s\"\n", dst2);
		char *r1=memcpy(dst1, src, n);
		char *r2=ft_memcpy(dst2, src, n);
		printf("APRES:dst1=\"%s\"\n", dst1);
		printf("APRES:dst2=\"%s\"\n", dst2);
		int r;
		if (strcmp(dst1, dst2)==0 && strcmp(r1, r2)==0)
			r = 0;
		else
			r = 1;
		printf("RES = %d\n", r);
		free(dst1);
		free(dst2);
		return (r);
	}
	else
	{
		size_t	size = strlen(src);
		char	*dst1 = (char *) calloc(size + 1, sizeof(char));
		if (!dst1)
			return (404);
		char 	*dst2 = (char *) calloc(size + 1, sizeof(char));
		if (!dst2)
		{
			free(dst1);
			return (404);
		}

		printf("AVANT: dst1:\"%s\"\n",dst1);
		printf("AVANT: dst2:\"%s\"\n",dst2);
		char *r1 = memcpy(dst1, src, n);
		char *r2 = ft_memcpy(dst2, src, n);
		printf("APRES: dst1:\"%s\"\n",dst1);
		printf("APRES: r1:\"%s\"\n",r1);
		printf("APRES: dst2:\"%s\"\n",dst2);
		printf("APRES: r2:\"%s\"\n",r2);

		if (strcmp(r1,dst1)==0 && strcmp(r2,dst2)==0 && strcmp(r1,r2)==0)
			nb_err=0;
		else
			nb_err=1;

		printf("nb_err = %d\n",nb_err);
		free(dst1);
		free(dst2);
		return (nb_err);
	}
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

int	compare_tab(int *tab, int tab_size, int size)
{
	int	nb_err = 0;
	int	*t1=(int *) calloc(tab_size, sizeof(int));
	if (!t1)
		return (404);
	int	*t2=(int *) calloc(tab_size, sizeof(int));
	if (!t2)
		return (404);

	printf("\nmemcpy(tab, %d)\n", size);
	printf("-AVANT:\nt1:");
	print_tab(t1,tab_size);
	printf("t2:");
	print_tab(t2,tab_size);

	memcpy(t1, tab, sizeof(int) * size);
	ft_memcpy(t2, tab, sizeof(int) * size);

	printf("-APRES:\nt1:");
	print_tab(t1,tab_size);
	printf("t2:");
	print_tab(t2,tab_size);

	for (int i=0;i<tab_size;i++)
		if (t1[i] != t2[i])
			nb_err++;

	free(t1);
	free(t2);
	return ((nb_err)?1:0);
}

int	main()
{
	int	tot_fail=0;
// -[ 	COMPARE STRING ]---------------------------------------------------------
    printf("\nTEST SUR CHAINES DE CARACTERES:\n");
	char *vide = "";
	char *s1 = "coucou";
    //tot_fail+=compare_str(NULL, 0);
    tot_fail+=compare_str(vide, 0);
    tot_fail+=compare_str(s1, 0);
    tot_fail+=compare_str(s1, 4);
    tot_fail+=compare_str(s1, 7);

// -[ 	COMPARE TABLEAUX ENTIERS ]-----------------------------------------------
    printf("\nTEST SUR TABLEAUX d'ENTIERS:\n");
	int	t0[0] = {};
	tot_fail+=compare_tab(t0, 0, 0);

	int	t1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (int i=0;i<=9;i++)
		tot_fail+=compare_tab(t1, 9, i);

	return (tot_fail);
}
