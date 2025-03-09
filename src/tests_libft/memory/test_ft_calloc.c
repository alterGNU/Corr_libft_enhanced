#include "libft.h"  // ft_calloc
#include <stdlib.h> // calloc
#include <stdio.h>  // printf, fprintf
#include <string.h> // strcat
#include "stdint.h" // SIZE_MAX
#include <limits.h> // INT_MAX, INT_MIN

#define BUFF 256

void	printblock(char *nom_block, void *pt, size_t nb_elem, size_t size_elem)
{
	char	res[BUFF];
	char	*block;
	char	cell[BUFF];

	block = (char *) pt; //cast pour parcourir la memoire bytes by bytes

	sprintf(res,"%s[",nom_block);
	for (size_t i=0;i<(nb_elem*size_elem);i++)
	{
		sprintf(cell,"%d",block[i]);
		strcat(res, cell);
		if ((i + 1 < nb_elem*size_elem) && !((i+1)%size_elem))
			strcat(res,",");
	}
	sprintf(cell,"]\n");
	strcat(res, cell);
	printf("%s",res);
}

int	compare_str(size_t nbe, size_t se)
{
	void    *real;
	void    *ft;
	int		res = 0;

	real	=  calloc(nbe, se);
	ft		=  ft_calloc(nbe, se);
	// AFFICHAGE SI VERBOSE
	// TESTS
	if (real && ft)            // Si real et ft sont non null on test leurs mem
	{
		printblock("real", real,  nbe, se);
		printblock("ft  ", ft,  nbe, se);
		if(memcmp(real, ft, nbe*se) != 0)
			res = 1;
	}
	else                     // Si un des deux est NULL alors l'autre l'est
		if ((!real && ft) || (real && !ft))
			res = 1;
	free(real);
	free(ft);
	return (res);

}

int	main()
{
	int	nb_err=0;
	//CAS PARTICULIER
	printf("\nCAS PARTICULIERS:\n");
	nb_err+=compare_str(0,0);     //--> &p  :tableau de taille zero de case zero
								 
	// MAX INT
	printf("\nCAS INT_MAX:\n");
	nb_err+=compare_str(INT_MAX,0);       //--> &p  :tableau de INT_MAX case toutes vident
	nb_err+=compare_str(0,INT_MAX);       //--> &p  :tableau de 0 case de taille INT_MAX
										 
	// Provoque erreur fsanitize car SURALLOCATION de memoire.
	//nb_err+=compare_str(INT_MAX,INT_MAX); //--> NULL:(trop grand) tab taille INT_MAX de case INT_MAX

	/* UNCOMMENT POUR VOIR LE FONCTIONNEMENT DU VRAI CALLOC MAIS BUG VALGRIND*/
	//printf("\nCAS SIZE_MAX:\n");
	
	// PROVOQUE ERROR VALGRIND
	//nb_err+=compare_str(0,SIZE_MAX);          //--> &p  :tableau de 0 case de taille SIZE_MAX
	//nb_err+=compare_str(SIZE_MAX,0);          //--> &p  :tableau de SIZE_MAX case de taille 0
	
	// PROVOQUE FAIL FSANITIZE CAR TENTATIVE DE SURALLOCATION
	//nb_err+=compare_str(1,SIZE_MAX - 1);          //--> NULL:(trop grand) tab de taille 1 de case SIZE_MAX
	//nb_err+=compare_str(SIZE_MAX - 1,1);          //--> NULL:(trop grand) tab de taille SIZE_MAX de case SIZE_MAX
	////nb_err+=compare_str(SIZE_MAX,SIZE_MAX);   //--> NULL:(trop grand) tab taille SIZE_MAX de case SIZE_MAX
	
	// TEST SANS LE VRAI POUR VOIR CE QUE FAIT LE MIENS
	printf("\nCAS INT_MAX:\n");
	void	*pt0 = ft_calloc(0,INT_MAX);
	nb_err+=(pt0 != NULL)?0:1;                  //--> &p  :tableau de 0 case de taille INT_MAX
	free(pt0);
	void	*pt1 = ft_calloc(INT_MAX,0);
	nb_err+=(pt1 != NULL)?0:1;                  //--> &p  :tableau de 0 case de taille INT_MAX
	free(pt1);
	void	*pt2 = ft_calloc(1,INT_MAX);
	nb_err+=(!pt2)?0:1;                         //--> NULL:(trop grand) tab de taille 1 de case INT_MAX
	free(pt2);
	void	*pt3 = ft_calloc(10,INT_MAX);
	nb_err+=(!pt3)?0:1;                         //--> NULL:(trop grand) tab de taille 1 de case INT_MAX
	free(pt3);
	void	*pt4 = ft_calloc(INT_MAX,1);
	nb_err+=(pt4 == NULL)?0:1;                  //--> NULL:(trop grand) tab de taille INT_MAX de case INT_MAX
	free(pt4);
	void	*pt5 = ft_calloc(INT_MAX,10);
	nb_err+=(pt5 == NULL)?0:1;                  //--> NULL:(trop grand) tab de taille INT_MAX de case INT_MAX
	free(pt5);
	void	*pt6 = ft_calloc(INT_MAX,INT_MAX);
	nb_err+=(pt6 == NULL)?0:1;                  //--> NULL:(trop grand) tab de taille INT_MAX de case INT_MAX
	free(pt6);

	//CAS type=str
	printf("\nCAS type=str:\n");
	for (size_t i=0;i<2;i++)
		nb_err+=compare_str(i,0);
	for (size_t i=0;i<4;i++)
		nb_err+=compare_str(i,sizeof(char));
	//CAS type=int
	printf("\nCAS type=int:\n");
	for (size_t i=0;i<4;i++)
		nb_err+=compare_str(i,sizeof(int));
	//CAS type=LONG LONG
	printf("\nCAS type=long long:\n");
	for (size_t i=0;i<4;i++)
		nb_err+=compare_str(i,sizeof(long long));

	return (nb_err);
}
