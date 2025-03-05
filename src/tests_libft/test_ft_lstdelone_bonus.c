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
	printf("\n");
	ft_lstshow(lst);
	print_tab(tab);

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

int	main()
{
	int	nb_err=0;

	char	*tab[]={"coucou","petite","perruche","!", NULL};

	char *s1 = strdup("perruche");
	if(!s1)
		return (404);
	t_list	*l1=ft_lstnew(s1);
	if(!l1)
		return (404);

	char *s2 = strdup("petite");
	if(!s2)
		return (404);
	t_list	*l2=ft_lstnew(s2);
	if(!l2)
		return (404);
	ft_lstadd_front(&l1, l2);

	char *s3 = strdup("coucou");
	if(!s3)
		return (404);
	t_list	*l3=ft_lstnew(s3);
	if(!l3)
		return (404);
	ft_lstadd_front(&l1, l3);

	char *s4 = strdup("!");
	if(!s4)
		return (404);
	t_list	*l4=ft_lstnew(s4);
	if(!l4)
		return (404);
	ft_lstadd_back(&l1, l4);


	int	i=0;
	nb_err+=check_list(l1,tab + i++);
	t_list	*suiv;
	while (l1)
	{
		suiv = l1->next;
		ft_lstdelone(l1, free);
		l1 = suiv;
		nb_err+=check_list(l1,tab + i++);
	}

	return (nb_err);
}
