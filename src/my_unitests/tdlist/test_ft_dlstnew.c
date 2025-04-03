#include "libft.h"  // struct t_list
#include <string.h> // strcmp
#include <stdio.h> // strcmp

void	print_dlst_node(void *ptr)
{
	ft_printf("<->%s<->", (char *)ptr);
}

int	main()
{
	int	nb_err = 0;
	// test_dlstnew
	t_dlist *n1 = ft_dlstnew(ft_strdup("n1"));
	ft_printf("new_node=");
	print_dlst_node(n1->content);
	ft_printf("\n");
	// ft_dlstdelone
	ft_dlstdelone(&n1, free);
	//ft_dlstadd_back();
	t_dlist *l1 = NULL;
	ft_dlstadd_back(&l1, ft_dlstnew(ft_strdup("noeud1")));
	ft_dlstadd_back(&l1, ft_dlstnew(ft_strdup("noeud2")));
	ft_dlstadd_back(&l1, ft_dlstnew(ft_strdup("noeud3")));
	//ft_dlstiter();
	ft_printf("l1=");
	ft_dlstiter(l1, print_dlst_node, 0);
	ft_printf("\n");
	//ft_dlstclear();
	ft_dlstclear(&l1, free);

	//ft_dlstadd_front();
	t_dlist *l2 = NULL;
	ft_dlstadd_front(&l2, ft_dlstnew(ft_strdup("noeud1")));
	ft_dlstadd_front(&l2, ft_dlstnew(ft_strdup("noeud2")));
	ft_dlstadd_front(&l2, ft_dlstnew(ft_strdup("noeud3")));
	//ft_dlstiter();
	ft_printf("l2=");
	ft_dlstiter(l2, print_dlst_node, 0);
	ft_printf("\n");
	//ft_dlstclear();
	ft_dlstclear(&l2, free);

	//ft_dlstadd_after();
	t_dlist *l3 = NULL;
	t_dlist *l3_n1 = ft_dlstnew(ft_strdup("noeud1"));
	t_dlist *l3_n2 = ft_dlstnew(ft_strdup("noeud2"));
	t_dlist *l3_n3 = ft_dlstnew(ft_strdup("noeud3"));
	ft_dlstadd_back(&l3, l3_n1);
	ft_dlstadd_back(&l3, l3_n2);
	ft_dlstadd_back(&l3, l3_n3);
	ft_printf("BEFORE l3=");
	ft_dlstiter(l3, print_dlst_node, 0);
	ft_printf("\n");
	ft_dlstadd_after(l3_n2,ft_dlstnew(ft_strdup("add after n2")));
	ft_printf("AFTER ADD_AFTER l3=");
	ft_dlstiter(l3, print_dlst_node, 0);
	ft_printf("\n");
	ft_dlstadd_before(l3_n2,ft_dlstnew(ft_strdup("add before n2")));
	// ft_printf("AFTER ADD_BEFORE l3=");
	// ft_dlstiter(l3, print_dlst_node, 0);

	//ft_dlstfirst();
	ft_printf("\nft_dlstfirst(l3_n3)=");
	print_dlst_node(ft_dlstfirst(l3_n2)->content);
	// ft_dlstlast();
	ft_printf("\n ft_dlstlast l3=");
	print_dlst_node(ft_dlstlast(l3_n1)->content);
	// ft_dlstsize();
	ft_printf("\n l3 ft_dlstsize==%d==%d==%d\n", ft_dlstsize(l3_n1), ft_dlstsize(l3_n2), ft_dlstsize(l3_n3));
	// ft_dlstclear();
	ft_dlstclear(&l3, free);

	//ft_dlstmap();
	return (nb_err);
}
