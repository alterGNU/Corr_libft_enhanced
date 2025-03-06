#include "libft.h" // ft_toupper
#include <ctype.h> // toupper
#include <stdio.h> // printf

int	compare(int c)
{
	int	    real;
	int	    ft;

	real = toupper(c);
	ft = ft_toupper(c);
	if (isprint(c))
		printf("toupper(%c) = [%c] == [%c]\n",c ,real ,ft);
	else
		printf("toupper(%d) = [%d] == [%d]\n",c ,real ,ft);
	return (real != ft);
}

int	main()
{
	int nb_err = 0;
	for(int i=0; i<178; i++)
		nb_err+=compare(i);

	return (nb_err);
}
