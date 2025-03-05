#include "libft.h"  //ft_strdup
#include <string.h> // strdup, strcmp
#include <stdio.h>  // printf

int	compare_str(const char *str)
{
	char    *real;
	char    *ft;
	int		res = 0;

	real = strdup(str);
	if (!real)
		return (1);
	ft = ft_strdup(str);
	if (!ft)
	{
		free(real);
		return (1);
	}

	printf("\nstr :\"%s\"\nreal:\"%s\"\nft  :\"%s\"\n",str,real,ft);

	if (strcmp(str, real) || strcmp(str, ft) || strcmp(real, ft))
		res = 1;
	free(real);
	free(ft);
	return (res);
}

int	main()
{
	int	nb_err=0;

	nb_err+=compare_str("");
	char	s0[4] = {'\0', '\0', '\0', '\0'};
	nb_err+=compare_str(s0);
	nb_err+=compare_str("coucou petite perruche");
	char	s1[4]={'1', 50, '3', '\0'};
	nb_err+=compare_str(s1);
	
	return (nb_err);
}
