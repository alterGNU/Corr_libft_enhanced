/*lvl|   tbtree 0 lvl
 * 0 |XX
 *******************************************************************************
 *lvl|   tbtree 1 lvl
 * 0 |  01
 * 1 |XX  XX
 *******************************************************************************
 *lvl|   tbtree 2 lvl
 * 0 |      01       sep: 0
 * 1 |  02      03   sep: 3
 * 2 |XX  XX  XX  XX sep: 1
 *******************************************************************************
 *lvl|   tbtree 3 lvl                                            tot_lvl:4
 * 0 |                              01                               sep:0
 * 1 |              02                              03               sep:15
 * 2 |      04              05              06              07       sep:7
 * 3 |  08      09      10      11      12      13      14      15   sep:3
 * 4 |XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX sep:1
 *******************************************************************************
 *lvl|   tbtree 4 lvl                                                                                                            tot_lvl:5
 * 0 |                                                              01                                                               sep:0
 * 1 |                              02                                                                  03                           sep:31
 * 2 |              04                              05                              06                              07               sep:15
 * 3 |      08              09              10              11              12              13              14              15       sep:7
 * 4 |  16      17      18      19      20      21      22      23      24      25      26      27      28      29      30      31   sep:3
 * 5 |XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX sep:1
 *******************************************************************************
 */
#include "libft.h"  // struct t_btree
#include <string.h> // strcmp, strdup
#include <stdio.h>  // fprintf
#define LEN 90
#define MAX_LEN 4
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

int	print_btree_char(void *ptr)
{
	if (!ptr)
		return (ft_printf("|XX|"));
	return (ft_printf("|%s|", ((char *)((t_btree *)ptr)->content)));
}

//void	print_btree_char_void(void *ptr)
//{
//	ft_printf("|%s|", ((char *)ptr));
//}

int	main()
{
	int	nb_err=0;
	// =[ CONTENT == STRING ]===================================================
	// -[ BTREE == NULL  ]------------------------------------------------------
	print_title("Clear on NULL");
	t_btree *t0 = create_tbtree_node(NULL);
	ft_btreeprint(t0, print_btree_char, MAX_LEN);
	ft_btreeclear(&t0, free);
	// -[ BTREE OF ONE NODE ]---------------------------------------------------
	print_title("Clear on one node tree");
	t_btree *ta1 = create_tbtree_node("01");
	//ft_btreeiter_dl_to_ur(ta1, print_btree_char_void);
	ft_btreeprint(ta1, print_btree_char, MAX_LEN);
	ft_btreeclear(&ta1, free);
	// -[ BTREE OF MULTIPLE NODES ]---------------------------------------------
	/*    tbtree 
	 *       1
	 *   2       3
	 * 4   5   6   7
	 */
	print_title("Clear on perfect multiple binary tree");
	t_btree *tb1 = create_tbtree_node("01");
	t_btree *tb2 = create_tbtree_node("02");
	t_btree *tb3 = create_tbtree_node("03");
	tb1->left = tb2;
	tb1->right = tb3;
	t_btree *tb4 = create_tbtree_node("04");
	t_btree *tb5 = create_tbtree_node("05");
	tb2->left = tb4;
	tb2->right = tb5;
	t_btree *tb6 = create_tbtree_node("06");
	t_btree *tb7 = create_tbtree_node("07");
	tb3->left = tb6;
	tb3->right = tb7;
	//ft_btreeiter_dl_to_ur(tb1, print_btree_char_void);
	ft_btreeprint(tb1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tb1, free);
	// -[ BTREE OF MULTIPLE NODES ]---------------------------------------------
	/*   tbtree 
	 *              01
	 *      02              03
	 *  04      05      06      07
	 *08  09  10  11  12  13  14  15
     *lvl|   tbtree 3 lvl                                            tot_lvl:4
     * 0 |                              01                               sep:0
     * 1 |              02                              03               sep:15
     * 2 |      04              05              06              07       sep:7
     * 3 |  08      09      10      11      12      13      14      15   sep:3
     * 4 |XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX sep:1
	 */
	print_title("Clear on perfect multiple binary tree");
	t_btree *tc1 = create_tbtree_node("01");
	t_btree *tc2 = create_tbtree_node("02");
	t_btree *tc3 = create_tbtree_node("03");
	tc1->left = tc2;
	tc1->right = tc3;
	t_btree *tc4 = create_tbtree_node("04");
	t_btree *tc5 = create_tbtree_node("05");
	tc2->left = tc4;
	tc2->right = tc5;
	t_btree *tc6 = create_tbtree_node("06");
	t_btree *tc7 = create_tbtree_node("07");
	tc3->left = tc6;
	tc3->right = tc7;
	t_btree *tc8 = create_tbtree_node("08");
	t_btree *tc9 = create_tbtree_node("09");
	tc4->left = tc8;
	tc4->right = tc9;
	t_btree *tc10 = create_tbtree_node("10");
	t_btree *tc11 = create_tbtree_node("11");
	tc5->left = tc10;
	tc5->right = tc11;
	t_btree *tc12 = create_tbtree_node("12");
	t_btree *tc13 = create_tbtree_node("13");
	tc6->left = tc12;
	tc6->right = tc13;
	t_btree *tc14 = create_tbtree_node("14");
	t_btree *tc15 = create_tbtree_node("15");
	tc7->left = tc14;
	tc7->right = tc15;
	//ft_btreeiter_dl_to_ur(tc1, print_btree_char_void);
	ft_btreeprint(tc1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tc1, free);
	/*lvl|   tbtree 4 lvl
	 * 0 |                                                              01
	 * 1 |                              02                                                                  03
	 * 2 |              04                              05                              06                              07
	 * 3 |      08              09              10              11              12              13              14              15
	 * 4 |  16      17      18      19      20      21      22      23      24      25      26      27      28      29      30      31
	 * 5 |XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX
	 **************************************************************************
	 */
	print_title("Clear on perfect multiple binary tree");
	t_btree *td1 = create_tbtree_node("01");
	t_btree *td2 = create_tbtree_node("02");
	t_btree *td3 = create_tbtree_node("03");
	td1->left = td2;
	td1->right = td3;
	t_btree *td4 = create_tbtree_node("04");
	t_btree *td5 = create_tbtree_node("05");
	td2->left = td4;
	td2->right = td5;
	t_btree *td6 = create_tbtree_node("06");
	t_btree *td7 = create_tbtree_node("07");
	td3->left = td6;
	td3->right = td7;
	t_btree *td8 = create_tbtree_node("08");
	t_btree *td9 = create_tbtree_node("09");
	td4->left = td8;
	td4->right = td9;
	t_btree *td10 = create_tbtree_node("10");
	t_btree *td11 = create_tbtree_node("11");
	td5->left = td10;
	td5->right = td11;
	t_btree *td12 = create_tbtree_node("12");
	t_btree *td13 = create_tbtree_node("13");
	td6->left = td12;
	td6->right = td13;
	t_btree *td14 = create_tbtree_node("14");
	t_btree *td15 = create_tbtree_node("15");
	td7->left = td14;
	td7->right = td15;
	t_btree *td16 = create_tbtree_node("16");
	t_btree *td17 = create_tbtree_node("17");
	td8->left = td16;
	td8->right = td17;
	t_btree *td18 = create_tbtree_node("18");
	t_btree *td19 = create_tbtree_node("19");
	td9->left = td18;
	td9->right = td19;
	t_btree *td20 = create_tbtree_node("20");
	t_btree *td21 = create_tbtree_node("21");
	td10->left = td20;
	td10->right = td21;
	t_btree *td22 = create_tbtree_node("22");
	t_btree *td23 = create_tbtree_node("23");
	td11->left = td22;
	td11->right = td23;
	t_btree *td24 = create_tbtree_node("24");
	t_btree *td25 = create_tbtree_node("25");
	td12->left = td24;
	td12->right = td25;
	t_btree *td26 = create_tbtree_node("26");
	t_btree *td27 = create_tbtree_node("27");
	td13->left = td26;
	td13->right = td27;
	t_btree *td28 = create_tbtree_node("28");
	t_btree *td29 = create_tbtree_node("29");
	td14->left = td28;
	td14->right = td29;
	t_btree *td30 = create_tbtree_node("30");
	t_btree *td31 = create_tbtree_node("31");
	td15->left = td30;
	td15->right = td31;
	//ft_btreeiter_dl_to_ur(td1, print_btree_char_void);
	ft_btreeprint(td1, print_btree_char, MAX_LEN);
	ft_btreeclear(&td1, free);
	return (nb_err);
}
