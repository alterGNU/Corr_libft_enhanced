#include "libft.h"      // struct t_btree
#include <string.h>     // strcmp, strdup
#include <stdio.h>      // fprintf
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

// test iteration
//void	print_btree_char_void(void *ptr)
//{
//	ft_printf("|%s|", ((char *)ptr));
//}
//ft_btreeiter_dl_to_ur(tpe1, print_btree_char_void);

int	main()
{
	int	nb_err=0;
	// =[ CONTENT == STRING ]===================================================
	// -[ BTREE == NULL  ]------------------------------------------------------
	/*
 	 * lvl|   tbtree 0 lvl
 	 * 0  |XX
	 */
	print_title("Clear on empty tree == NULL");
	t_btree *t0 = create_tbtree_node(NULL);
	ft_btreeprint(t0, print_btree_char, MAX_LEN);
	ft_btreeclear(&t0, free);
	// -[ PERFECT TREE OF 1 LVL ]-----------------------------------------------
 	/*
 	 * lvl|   Prefect tbtree 1 lvl, one node
 	 *  0 |  01
 	 *  1 |XX  XX
 	 */
	print_title("Clear on tree of one lvl");
	t_btree *tpa1 = create_tbtree_node("01");
	ft_btreeprint(tpa1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tpa1, free);
	// -[ PERFECT TREE OF 2 LVL ]-----------------------------------------------
	/*
 	 * lvl|   Perfect tbtree 2 lvl, 3 nodes
 	 *  0 |      01       sep: 0
 	 *  1 |  02      03   sep: 3
 	 *  2 |XX  XX  XX  XX sep: 1
 	 */
	print_title("Clear on perfect tree of 2 levels == 3nodes");
	t_btree *tpb1 = create_tbtree_node("01");
	t_btree *tpb2 = create_tbtree_node("02");
	t_btree *tpb3 = create_tbtree_node("03");
	tpb1->left = tpb2;
	tpb1->right = tpb3;
	ft_btreeprint(tpb1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tpb1, free);
	// -[ PERFECT TREE OF 3 LVL ]-----------------------------------------------
	/*
 	 * lvl|   Perfect tbtree 3 lvl, 7 nodes
 	 *  0 |              01                sep: 0
 	 *  1 |      02              03        sep: 7
 	 *  2 |  04      05      06      07    sep: 3
 	 *  3 |XX  XX  XX  XX  XX  XX  XX  XX  sep: 1
 	 */
	print_title("Clear on perfect tree of 2 levels == 7nodes");
	t_btree *tpc1 = create_tbtree_node("01");
	t_btree *tpc2 = create_tbtree_node("02");
	t_btree *tpc3 = create_tbtree_node("03");
	tpc1->left = tpc2;
	tpc1->right = tpc3;
	t_btree *tpc4 = create_tbtree_node("04");
	t_btree *tpc5 = create_tbtree_node("05");
	tpc2->left = tpc4;
	tpc2->right = tpc5;
	t_btree *tpc6 = create_tbtree_node("06");
	t_btree *tpc7 = create_tbtree_node("07");
	tpc3->left = tpc6;
	tpc3->right = tpc7;
	ft_btreeprint(tpc1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tpc1, free);
	// -[ NOT PERFECT TREE OF 3 LVL ]-------------------------------------------
	/*
 	 * lvl|   Perfect tbtree 3 lvl, 7 nodes
 	 *  0 |              01                sep: 0
 	 *  1 |      02              03        sep: 7
 	 *  2 |  XX      05      06      XX    sep: 3
 	 *  3 |XX  XX  XX  XX  XX  XX  XX  XX  sep: 1
 	 */
	print_title("Clear on NOT perfect tree of 3 levels == 5nodes");
	t_btree *tua1 = create_tbtree_node("01");
	t_btree *tua2 = create_tbtree_node("02");
	t_btree *tua3 = create_tbtree_node("03");
	tua1->left = tua2;
	tua1->right = tua3;
	t_btree *tua5 = create_tbtree_node("05");
	tua2->right = tua5;
	t_btree *tua6 = create_tbtree_node("06");
	tua3->left = tua6;
	ft_btreeprint(tua1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tua1, free);
	// -[ NOT PERFECT TREE OF 3 LVL ]-------------------------------------------
	/*
 	 * lvl|   Perfect tbtree 3 lvl, 3 nodes
 	 *  0 |              01                sep: 0
 	 *  1 |      02              XX        sep: 7
 	 *  2 |  04      XX      XX      XX    sep: 3
 	 *  3 |XX  XX  XX  XX  XX  XX  XX  XX  sep: 1
 	 */
	print_title("Clear on perfect tree of 3 levels == 3nodes");
	t_btree *tub1 = create_tbtree_node("01");
	t_btree *tub2 = create_tbtree_node("02");
	tub1->left = tub2;
	t_btree *tub4 = create_tbtree_node("04");
	tub2->left = tub4;
	ft_btreeprint(tub1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tub1, free);
	// -[ NOT PERFECT TREE OF 3 LVL ]-------------------------------------------
	/*
 	 * lvl|   Perfect tbtree 3 lvl, 7 nodes
 	 *  0 |              01                sep: 0
 	 *  1 |      02              XX        sep: 7
 	 *  2 |  XX      05      XX      XX    sep: 3
 	 *  3 |XX  XX  XX  XX  XX  XX  XX  XX  sep: 1
 	 */
	print_title("Clear on perfect tree of 3 levels == 3nodes");
	t_btree *tuc1 = create_tbtree_node("01");
	t_btree *tuc2 = create_tbtree_node("02");
	tuc1->left = tuc2;
	t_btree *tuc5 = create_tbtree_node("05");
	tuc2->right = tuc5;
	ft_btreeprint(tuc1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tuc1, free);
	// -[ PERFECT TREE OF 4 LVL ]-----------------------------------------------
	/*
 	 * lvl|   Perfcet tbtree 3 lvl, 15 nodes                          tot_lvl:4
 	 *  0 |                              01                               sep:0
 	 *  1 |              02                              03               sep:15
 	 *  2 |      04              05              06              07       sep:7
 	 *  3 |  08      09      10      11      12      13      14      15   sep:3
 	 *  4 |XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX sep:1
 	 */
	print_title("Clear on perfect tree of 4 levels == 15nodes");
	t_btree *tpd1 = create_tbtree_node("01");
	t_btree *tpd2 = create_tbtree_node("02");
	t_btree *tpd3 = create_tbtree_node("03");
	tpd1->left = tpd2;
	tpd1->right = tpd3;
	t_btree *tpd4 = create_tbtree_node("04");
	t_btree *tpd5 = create_tbtree_node("05");
	tpd2->left = tpd4;
	tpd2->right = tpd5;
	t_btree *tpd6 = create_tbtree_node("06");
	t_btree *tpd7 = create_tbtree_node("07");
	tpd3->left = tpd6;
	tpd3->right = tpd7;
	t_btree *tpd8 = create_tbtree_node("08");
	t_btree *tpd9 = create_tbtree_node("09");
	tpd4->left = tpd8;
	tpd4->right = tpd9;
	t_btree *tpd10 = create_tbtree_node("10");
	t_btree *tpd11 = create_tbtree_node("11");
	tpd5->left = tpd10;
	tpd5->right = tpd11;
	t_btree *tpd12 = create_tbtree_node("12");
	t_btree *tpd13 = create_tbtree_node("13");
	tpd6->left = tpd12;
	tpd6->right = tpd13;
	t_btree *tpd14 = create_tbtree_node("14");
	t_btree *tpd15 = create_tbtree_node("15");
	tpd7->left = tpd14;
	tpd7->right = tpd15;
	ft_btreeprint(tpd1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tpd1, free);
	// -[ UNPERFECT TREE OF 4 LVL ]---------------------------------------------
	/*
 	 * lvl|   Perfcet tbtree 3 lvl, 15 nodes                          tot_lvl:4
 	 *  0 |                              01                               sep:0
 	 *  1 |              02                              03               sep:15
 	 *  2 |      04              XX              XX              07       sep:7
 	 *  3 |  XX      09      XX      XX      XX      XX      XX      15   sep:3
 	 *  4 |XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX sep:1
 	 */
	print_title("Clear on UNPERFECT tree of 4 levels == 7nodes");
	t_btree *tud1 = create_tbtree_node("01");
	t_btree *tud2 = create_tbtree_node("02");
	t_btree *tud3 = create_tbtree_node("03");
	tud1->left = tud2;
	tud1->right = tud3;
	t_btree *tud4 = create_tbtree_node("04");
	tud2->left = tud4;
	t_btree *tud7 = create_tbtree_node("07");
	tud3->right = tud7;
	t_btree *tud9 = create_tbtree_node("09");
	tud4->right = tud9;
	t_btree *tud15 = create_tbtree_node("15");
	tud7->right = tud15;
	ft_btreeprint(tud1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tud1, free);
	// -[ PERFECT TREE OF 5 LVL ]-----------------------------------------------
	/*
 	 * lvl|   Perfect tbtree 5 lvl, 31 nodes                                                                                          tot_lvl:5
 	 *  0 |                                                              01                                                               sep:0
 	 *  1 |                              02                                                                  03                           sep:31
 	 *  2 |              04                              05                              06                              07               sep:15
 	 *  3 |      08              09              10              11              12              13              14              15       sep:7
 	 *  4 |  16      17      18      19      20      21      22      23      24      25      26      27      28      29      30      31   sep:3
 	 *  5 |XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX  XX sep:1
 	*/
	print_title("Clear on perfect tree of 5 levels == 15nodes");
	t_btree *tpe1 = create_tbtree_node("01");
	t_btree *tpe2 = create_tbtree_node("02");
	t_btree *tpe3 = create_tbtree_node("03");
	tpe1->left = tpe2;
	tpe1->right = tpe3;
	t_btree *tpe4 = create_tbtree_node("04");
	t_btree *tpe5 = create_tbtree_node("05");
	tpe2->left = tpe4;
	tpe2->right = tpe5;
	t_btree *tpe6 = create_tbtree_node("06");
	t_btree *tpe7 = create_tbtree_node("07");
	tpe3->left = tpe6;
	tpe3->right = tpe7;
	t_btree *tpe8 = create_tbtree_node("08");
	t_btree *tpe9 = create_tbtree_node("09");
	tpe4->left = tpe8;
	tpe4->right = tpe9;
	t_btree *tpe10 = create_tbtree_node("10");
	t_btree *tpe11 = create_tbtree_node("11");
	tpe5->left = tpe10;
	tpe5->right = tpe11;
	t_btree *tpe12 = create_tbtree_node("12");
	t_btree *tpe13 = create_tbtree_node("13");
	tpe6->left = tpe12;
	tpe6->right = tpe13;
	t_btree *tpe14 = create_tbtree_node("14");
	t_btree *tpe15 = create_tbtree_node("15");
	tpe7->left = tpe14;
	tpe7->right = tpe15;
	t_btree *tpe16 = create_tbtree_node("16");
	t_btree *tpe17 = create_tbtree_node("17");
	tpe8->left = tpe16;
	tpe8->right = tpe17;
	t_btree *tpe18 = create_tbtree_node("18");
	t_btree *tpe19 = create_tbtree_node("19");
	tpe9->left = tpe18;
	tpe9->right = tpe19;
	t_btree *tpe20 = create_tbtree_node("20");
	t_btree *tpe21 = create_tbtree_node("21");
	tpe10->left = tpe20;
	tpe10->right = tpe21;
	t_btree *tpe22 = create_tbtree_node("22");
	t_btree *tpe23 = create_tbtree_node("23");
	tpe11->left = tpe22;
	tpe11->right = tpe23;
	t_btree *tpe24 = create_tbtree_node("24");
	t_btree *tpe25 = create_tbtree_node("25");
	tpe12->left = tpe24;
	tpe12->right = tpe25;
	t_btree *tpe26 = create_tbtree_node("26");
	t_btree *tpe27 = create_tbtree_node("27");
	tpe13->left = tpe26;
	tpe13->right = tpe27;
	t_btree *tpe28 = create_tbtree_node("28");
	t_btree *tpe29 = create_tbtree_node("29");
	tpe14->left = tpe28;
	tpe14->right = tpe29;
	t_btree *tpe30 = create_tbtree_node("30");
	t_btree *tpe31 = create_tbtree_node("31");
	tpe15->left = tpe30;
	tpe15->right = tpe31;
	ft_btreeprint(tpe1, print_btree_char, MAX_LEN);
	ft_btreeclear(&tpe1, free);
	return (nb_err);
}
