#include "libft.h"  // struct t_list
#include <stdio.h>  // printf
#include <string.h> // strcmp

void	print_tab(char **tab)
{
	size_t i;

	printf("tab : [");
	i = 0;
	while (tab[i])
	{
		printf("\"%s\", ",tab[i]);
		i++;
	}
	printf("\"NULL\"");
	printf("]\n");
}

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

int	check_list(t_list *lst, char **tab)
{
	t_list	*actual;
	actual = lst;
	while (*tab && actual)
	{
		if (strcmp(*tab, actual->content))
			return (1);
		actual = actual->next;
		tab++;
	}
	if ((*tab && !actual) || (!*tab && actual))
		return (1);
	return (0);
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

	t_list	*l1=ft_lstnew("coucou");
	ft_lstadd_back(&l1, NULL);
	ft_lstadd_back(&l1, ft_lstnew("petite"));
	ft_lstadd_back(&l1, NULL);
	ft_lstadd_back(&l1, ft_lstnew("perruche"));
	ft_lstadd_back(&l1, NULL);
	ft_lstshow(l1);

	char	*t1[]={"coucou","petite","perruche", NULL};
	print_tab(t1);

	nb_err+=check_list(l1,t1);
	free_list(&l1);
	return (nb_err);
}
