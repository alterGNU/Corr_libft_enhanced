#include "libft.h"  // struct t_list
#include <stdio.h>  // printf
#include <string.h> // strcmp

int	main()
{
	t_list	*l1=ft_lstnew(strdup("perruche"));
	if (!l1)
		return (404);

	char	*s2=strdup("petite");
	if (!s2)
		return (404);
	t_list	*l2=ft_lstnew(s2);
	if (!l2)
		return (404);
	ft_lstadd_front(&l1, l2);

	char	*s3=strdup("coucou");
	if (!s3)
		return (404);
	t_list	*l3=ft_lstnew(s3);
	if (!l3)
		return (404);
	ft_lstadd_front(&l1, l3);

	char	*s4=strdup("!");
	if (!s4)
		return (404);
	t_list	*l4=ft_lstnew(s4);
	if (!l4)
		return (404);
	ft_lstadd_front(&l1, l4);

	ft_lstclear(&l1, free);
	printf("REGARDEZ LE VALGRIND\n");
	return (0);
}
