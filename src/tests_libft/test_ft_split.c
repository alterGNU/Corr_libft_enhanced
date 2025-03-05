#include "libft.h"
#include <string.h> // strcomp
#include <stdio.h>  // printf

int	compare_tab(char *t1[], char *t2[])
{
	int	len_t1 = 0;
	int	len_t2 = 0;

	while (t1[len_t1])
		len_t1++;
	while (t2[len_t2])
		len_t2++;
	if (len_t1 != len_t2)
		return (1);
	int	i = 0;
	while (i < len_t1 - 1)
	{
		if (strcmp(t1[i],t2[i]))
			return (1);
		i++;
	}
	return (0);
}

void	affiche_tab(char **t1)
{
	if (!t1)
		return ;
	printf("[");
	int i = 0;
	while(t1[i])
	{
		printf("\"%s\"", t1[i]);
		if (t1[i + 1])
			printf(", ");
		i++;
	}
	printf("]\n");
}

int	test(const char *src, char c, char *res[])
{
	printf("ft_split(\"%s\", '%c')\n",src,c);
	affiche_tab(res);

	char **ft_res = ft_split(src, c);
	if (!ft_res)
		return (0);

	if (!src)
	{
		printf("src=NULL :");
		if (!ft_res)
		{
			printf("----> PASS\n\n");
			return (0);
		}
		printf("----> FAIL\n\n");
		return (1);
	}
	affiche_tab(ft_res);

	int r = compare_tab(res, ft_res);
	printf((r)?"----> FAIL\n\n":"----> PASS\n\n");

	int i = 0;
	while (ft_res[i])
	{
		free(ft_res[i]);
		i++;
	}
	free(ft_res);
	return (r);
}

int	main()
{
	int	tot_fail=0;


	char	*t0[] = {NULL};
	char	*s0 = NULL;
    printf("\n\t- CAS source NULL:\n");
	tot_fail+=test(s0, 'c', t0);

    printf("\n\t- CAS sep = 0:\n");
	char *t0t0[] = {"toto", NULL};
	tot_fail+=test("toto", 0, t0t0);
	tot_fail+=test("", 0, t0);
	tot_fail+=test(s0, 0, t0);

    printf("\n    - CAS source non vide:\n");
	char *t1[] = {"Hello", "World" ,"!" , NULL};
	tot_fail+=test("   Hello    World !  ", ' ', t1);

	char *t2[] = {"coucou petite perruche", NULL};
	tot_fail+=test("coucou petite perruche", 'x', t2);
	tot_fail+=test("coucou petite perruche.", '.', t2);
	tot_fail+=test(".coucou petite perruche", '.', t2);
	tot_fail+=test(".coucou petite perruche.", '.', t2);

	char *t2bis[] = {"coucou", "petite", "perruche", NULL};
	tot_fail+=test("coucou petite perruche", ' ', t2bis);

	char *t2ter[] = {"coucou p", "tit", " p", "rruch", NULL};
	tot_fail+=test("coucou petite perruche", 'e', t2ter);

	char *t2qua[] = {"ou", "ou petite perru", "he", NULL};
	tot_fail+=test("coucou petite perruche", 'c', t2qua);

	char *t3[] = {"42", NULL};
	tot_fail+=test("   42   ", ' ', t3);
	tot_fail+=test("42", ' ', t3);
	tot_fail+=test("       ", ' ', t0);
	tot_fail+=test("", ' ', t0);
	
	char *t4[] = {"a", "b", "c", NULL};
	tot_fail+=test("a b c", ' ', t4);
	tot_fail+=test("   a     b      c", ' ', t4);
	tot_fail+=test("a     b      c     ", ' ', t4);
	tot_fail+=test("   a     b      c     ", ' ', t4);

	char *t5[] = {"ab", "cd", NULL};
	tot_fail+=test("ab cd", ' ', t5);

	return (tot_fail);
}
