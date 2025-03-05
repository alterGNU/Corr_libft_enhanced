#include "libft.h"  // struct t_list
#include <stdio.h>  // printf
#include <string.h> // strcmp

static void print_all(void *content)
{
	printf("Content: %s\n", (char *)content);
}

static void print_address(void *content)
{
	printf("@ddress: %p\n", content);
}

int	main()
{
	char *s1 = strdup("perruche");
	if (!s1)
		return (404);
	t_list	*l1=ft_lstnew(s1);
	if (!l1)
		return (404);

	char *s2 = strdup("petite");
	if (!s2)
		return (404);
	t_list	*l2=ft_lstnew(s2);
	if (!l2)
		return (404);
	ft_lstadd_front(&l1, l2);

	char *s3 = strdup("coucouc");
	if (!s3)
		return (404);
	t_list	*l3=ft_lstnew(s3);
	if (!l3)
		return (404);
	ft_lstadd_front(&l1, l3);

	ft_lstiter(l1, print_all);
	ft_lstiter(l1, print_address);

	ft_lstclear(&l1,free);
	return (0);
}
