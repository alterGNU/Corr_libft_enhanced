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

int	check_last(t_list *lst, char *content)
{
	t_list *last = ft_lstlast(lst);
	printf("\nVoici la liste chainee a cette instant:\n");
	ft_lstshow(lst);
	printf("Le dernier element retourner par ft_lstlast est :");
	printf("[%s] vs [%s]\n",(char *)last->content,content);
	return (strcmp(last->content, content));
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

	t_list	*l1=ft_lstnew("perruche");
	if (!l1)
		return (404);
	nb_err+=check_last(l1, "perruche");

	t_list	*l2=ft_lstnew("petite");
	if (!l2)
		return (404);
	ft_lstadd_front(&l1, l2);
	nb_err+=check_last(l1, "perruche");

	t_list	*l3=ft_lstnew("coucou");
	if (!l3)
		return (404);
	ft_lstadd_front(&l1, l3);
	nb_err+=check_last(l1, "perruche");

	free_list(&l1);
	return (nb_err);
}
