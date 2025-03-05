#include "libft.h"  // struct t_list
#include <stdio.h>  // printf
#include <string.h> // strcmp

void	ft_lstshow(t_list *lst)
{
	printf("t_list : ");
	while (lst)
	{
		if (lst)
			printf("[%s]-->",(char *)lst->content);
		lst = lst->next;
	}
	printf("[NULL]\n");
}

void	free_list(t_list **lst)
{
	t_list	*actual;
	t_list	*suiv;
	actual = *lst;
	while (actual)
	{
		suiv = actual->next;
		free(actual);
		actual = suiv;
	}
	*lst = NULL;
}

int	main()
{
	int	nb_err=0;

	nb_err+=((int)(ft_lstsize(NULL) != 0));
	printf("ft_lstsize(NULL) retourne %d\n\n", ft_lstsize(NULL));

	t_list	*l1=ft_lstnew("perruche");
	if (!l1)
		return (1);
	nb_err+=((int)(ft_lstsize(l1) != 1));
	ft_lstshow(l1);
	printf("La fonction ft_lstsize retourne %d\n\n", ft_lstsize(l1));

	t_list	*l2=ft_lstnew("petite");
	if (!l2)
		return (1);
	ft_lstadd_front(&l1, l2);
	nb_err+=((int)(ft_lstsize(l1) != 2));
	ft_lstshow(l1);
	printf("La fonction ft_lstsize retourne %d\n\n", ft_lstsize(l1));

	t_list	*l3=ft_lstnew("coucou");
	if (!l3)
		return (1);
	ft_lstadd_front(&l1, l3);
	nb_err+=((int)(ft_lstsize(l1) != 3));
	ft_lstshow(l1);

	printf("La fonction ft_lstsize retourne %d\n\n", ft_lstsize(l1));

	free_list(&l1);
	return (nb_err);
}
