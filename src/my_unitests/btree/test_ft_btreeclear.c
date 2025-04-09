#include "libft.h"  // struct t_btree
#include <string.h> // strcmp, strdup
#include <stdio.h>  // fprintf
#define LEN 90
#define CE "\033[0m"    // COLOR END
#define CR "\033[0;31m" // COLOR RED
#define CV "\033[0;32m" // COLOR GREEN
#define CM "\033[0;33m" // COLOR BROWN
#define CY "\033[0;93m" // COLOR YELLOW
#define CB "\033[0;36m" // COLOR AZURE
#define CG "\033[0;37m" // COLOR GREY
#define PASS "> \033[37;42m ✓ \033[0m\n"
#define	FAIL "> \033[30;41m ✗ \033[0m\n"

int	printntime(char c, int n)
{
	for (int i = 0 ; i < n; i++)
		ft_printf("%c", c);
	return (n);
}

void print_title(const char *title)
{
	ft_printf("\033[97;100m");
	int print_sofar = ft_printf("=[ %s ]", title);
	printntime('=', LEN - print_sofar);
	ft_printf("\033[0m\n");
}

// =[ TEST CONTENT == STRING ]==================================================
int	print_btree_content_is_char(t_btree *btree_node)
{
	if (!btree_node)
		return (ft_printf("NULL"));
	return (ft_printf("{c->%s ,l->%p, r->%p}", btree_node->content, btree_node->left, btree_node->right));
}

t_btree	*create_tbtree_node(const char *str)
{
	char	*dup_str;
	t_btree	*res;

	if (!str)
		return (NULL);
	dup_str = strdup(str);
	if (!dup_str)
	{
		fprintf(stderr, CR"strdup()->NULL"CE);
		exit(42);
	}
	res = ft_btreenew(dup_str);
	if (!res)
	{
		fprintf(stderr, CR"ft_btreenew()->NULL"CE);
		exit(42);
	}
	return (res);

}

int	main()
{
	int	nb_err=0;
	// =[ CONTENT == STRING ]===================================================
	// -[ BTREE == NULL  ]------------------------------------------------------
	print_title("Clear on NULL");
	t_btree *t0 = create_tbtree_node(NULL);
	ft_btreeclear(&t0, free);
	// -[ BTREE OF ONE NODE ]---------------------------------------------------
	print_title("Clear on one node tree");
	t_btree *ta1 = create_tbtree_node("node ta1");
	ft_btreeclear(&ta1, free);
	// -[ BTREE OF MULTIPLE NODES ]---------------------------------------------
	/*    tbtree 
	 *       1
	 *   2       3
	 * 4   5   6   7
	 */
	print_title("Clear on perfect multiple binary tree");
	t_btree *tb1 = create_tbtree_node("node 1");
	t_btree *tb2 = create_tbtree_node("node 2");
	t_btree *tb3 = create_tbtree_node("node 3");
	tb1->left = tb2;
	tb1->right = tb3;
	t_btree *tb4 = create_tbtree_node("node 4");
	t_btree *tb5 = create_tbtree_node("node 5");
	tb2->left = tb4;
	tb2->right = tb5;
	t_btree *tb6 = create_tbtree_node("node 6");
	t_btree *tb7 = create_tbtree_node("node 7");
	tb3->left = tb6;
	tb3->right = tb7;
	ft_btreeclear(&tb1, free);
	return (nb_err);
}
