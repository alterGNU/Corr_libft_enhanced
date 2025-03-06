#include "libft.h" // ft_tolower
#include <ctype.h> // tolower, isprint
#include <stdio.h> // printf

int	compare(int c)
{
	int	    real;
	int	    ft;

	real = tolower(c);
	ft = ft_tolower(c);
	if (isprint(c))
		printf("tolower(%c) = [%c] == [%c]\n",c ,real ,ft);
	else
		printf("tolower(%d) = [%d] == [%d]\n",c ,real ,ft);
	return (real != ft);
}

int	main()
{
	int nb_err = 0;
	for(int i=0; i<178; i++)
		nb_err+=compare(i);

	return (nb_err);
}
