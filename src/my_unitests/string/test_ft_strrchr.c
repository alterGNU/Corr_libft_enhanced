#include "libft.h"  // ft_strrchr
#include <string.h> // strrchr
#include <stdio.h>  // printf
#include <ctype.h>  // isprint

int	compare(const char *str, int c)
{
	char	*real;
	char	*ft;

	real = strrchr(str, c);
	ft = ft_strrchr(str, c);
	if (isprint(c))
		printf("strchr(\"%s\", %c) = real<%s> == ft<%s>\t", str, c ,real ,ft);
	else
		printf("strchr(\"%s\", %d) = real<%s> == ft<%s>\t", str, c ,real ,ft);
	int r = (real == ft);
	printf(r?"--------> PASS!\n" : "--------> FAIL!\n");
	return (!r);
}

int	main()
{
	int	nb_err=0;
	// CAS CHaine vide et NE contient PAS c
	printf("\nCAS Chaine vide et NE contient PAS c\n");
	nb_err+=compare("", 'e');
	
	// CAS Chaine vide et contient c='\0'
	printf("\nCAS Chaine vide et contient c=0\n");
	nb_err+=compare("", 0);
	
	// CAS Chaine NON VIDE et contient c='\0'
	printf("\nCAS Chaine NON VIDE et contient c=0\n");
	nb_err+=compare("coucou petite perruche", '\0');

	// CAS Chaine NON VIDE et contient c
	printf("\nCAS Chaine NON VIDE et contient c\n");
	nb_err+=compare("coucou petite perruche", 'c');
	nb_err+=compare("coucou petite perruche", 'o');
	nb_err+=compare("coucou petite perruche", 'u');
	nb_err+=compare("coucou petite perruche", ' ');
	nb_err+=compare("coucou petite perruche", 'p');
	nb_err+=compare("coucou petite perruche", 'e');
	nb_err+=compare("coucou petite perruche", 'i');
	nb_err+=compare("coucou petite perruche", 'r');
	nb_err+=compare("coucou petite perruche", 'h');
	nb_err+=compare("coucou petite perruche", '\0');
	
	// CAS Chaine NON VIDE et NE contient PAS c
	printf("\nCAS Chaine NON VIDE et NE contient PAS c\n");
	nb_err+=compare("coucou petite perruche", 'z');
	
	// CAS OS (Forcement silencieux)
	for (int i=-200;i<210;i++)
		nb_err+=compare("coucou petite perruche", i);
	
	return (nb_err);
}
