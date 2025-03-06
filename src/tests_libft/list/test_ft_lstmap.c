#include "libft.h"  // struct t_list
#include <stdio.h>  // printf
#include <string.h> // strcmp
#include <ctype.h> // isupper

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

int	compare_list(t_list *l1, t_list *l2)
{
	if (!l1 || !l2)
		return (1);
	int	s1 = ft_lstsize(l1);
	int	s2 = ft_lstsize(l2);
	if (s1 != s2)
		return (1);

	while (l1 && l2)
	{
		char *s1 = (char *) l1->content;
		if (!s1)
			return (1);
		char *s2 = (char *) l2->content;
		if (!s2)
			return (1);
		size_t len1 = ft_strlen(s1);
		size_t len2 = ft_strlen(s2);
		if (len1 != len2)
			return (1);
		for(size_t i = 0; i < len1; i++)
		{
			char c1 = s1[i];
			char c2 = s2[i];
			if (ft_isalpha(c1) && (!isupper(c2) || (c1 != ft_tolower(c2))))
				return (1);
		}
		l1 = l1->next;
		l2 = l2->next;
	}
	return (0);
}

void	to_upper(unsigned int i, char *str)
{
	if (!str)
		return ;
	(void) i;
	*str = (unsigned char)ft_toupper((unsigned char)*str);
}

void	*all_to_upper(void *content)
{
	char	*str;
	char	*res;

	if (!content)
		return (NULL);
	str = (char *)content;
	res = strdup(str);
	if (!res)
		return (NULL);
	ft_striteri(res, to_upper);
	return (res);
}

void	free_node(void *content)
{
	free(content);
}

int	main()
{
	int	nb_error = 0;
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

	char *s3 = strdup("coucou");
	if (!s3)
		return (404);
	t_list	*l3=ft_lstnew(s3);
	if (!l3)
		return (404);
	ft_lstadd_front(&l1, l3);

	char *s4 = strdup("!");
	if (!s4)
		return (404);
	t_list	*l4=ft_lstnew(s4);
	if (!l4)
		return (404);
	ft_lstadd_front(&l1, l4);

	t_list	*newl1=ft_lstmap(l1, all_to_upper, free);
	if (!newl1)
	{
		return (404);
	}

	ft_lstshow(l1);
	ft_lstshow(newl1);

	nb_error+=compare_list(l1, newl1);

	ft_lstclear(&l1,free);
	ft_lstclear(&newl1,free);
	return (nb_error);
}
