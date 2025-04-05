#include "libft.h"  // struct t_list
#include "string.h" // strcmp, strdup

// =[ TEST CONTENT == STRING ]==================================================
int	print_btree_content_is_char(t_btree *btree_node)
{
	if (!btree_node)
		return (ft_printf("NULL"));
	return (ft_printf("{c->%s ,l->%p, r->%p}", btree_node->content, btree_node->left, btree_node->right));
}

void free_btree_node_char(t_btree *node)
{
	if (!node)
		return;
	if (node->content)
	{
		free(node->content);
		node->content = NULL;
	}
	free(node);
	node = NULL;
}

int	test_char(const char *str)
{
	ft_printf("ft_btreenew(%s)-->", str);
	t_btree *node;

	if (!str)
	{
		node = ft_btreenew(NULL);
		print_btree_content_is_char(node);
		ft_printf("\n");
		if (!node)
			return (1);
		if (!node->content)
			return (free_btree_node_char(node), 0);
		return (free_btree_node_char(node), 1);
	}
	char *content = ft_strdup(str);
	if (!content)
		exit(42);
	node = ft_btreenew(content);
	print_btree_content_is_char(node);
	ft_printf("\n");
	if (!node)
		return (free(content), 1);
	if (!strcmp(node->content, str))
		return (free_btree_node_char(node), 0);
	return (free_btree_node_char(node), 1);
}

// =[ TEST CONTENT == STRING ARRAY ]============================================
int	print_btree_content_is_chararray(t_btree *btree_node)
{
	int	print_sofar = 0;
	if (!btree_node)
		return (ft_printf("NULL"));
	print_sofar += ft_printf("{c->");
	print_sofar += ft_print_str_array((char **)btree_node->content);
	print_sofar += ft_printf(" ,l->%p, r->%p}", btree_node->left, btree_node->right);
	return (print_sofar);
}

void free_btree_node_chararray(t_btree *node)
{
	if (!node)
		return;
	if (node->content)
	{
		char **arr = node->content;
		ft_free_str_array(&arr);
		node->content = NULL;
	}
	free(node);
	node = NULL;
}

int	test_chararray(const char **array)
{
	// Print this test
	ft_printf("ft_btreenew(");
	ft_print_str_array((char **)array);
	ft_printf(")-->");
	t_btree *node;
	// CASE 1: array == NULL
	if (!array || !*array)
	{
		node = ft_btreenew(NULL);
		print_btree_content_is_char(node);
		ft_printf("\n");
		if (!node)
			return (1);
		if (!node->content)
			return (free_btree_node_chararray(node), 0);
		return (free_btree_node_chararray(node), 1);
	}
	// CASE 2: array != NULL
	// Duplicate const char **array dynamically and create node->content
	int i=0;
	while(array[i])
		i++;
	char **content = (char **) calloc(i + 1, sizeof(char *));
	if (!content)
		exit(42);
	i = -1;
	while (array[++i])
	{
		content[i] = strdup(array[i]);
		if (!content[i])
		{
			ft_free_str_array(&content);
			exit(42);
		}
	}
	node = ft_btreenew(content);
	print_btree_content_is_chararray(node);
	ft_printf("\n");
	// Check results
	if (!node || !node->content)
		return (ft_free_str_array(&content), 1);
	i = 0;
	char **act = (char **)(node->content);
	while (act[i] && array[i])
	{
		if (strcmp(act[i], array[i]))
			return (free_btree_node_chararray(node), 1);
		i++;
	}
	if (act[i] || array[i])
		return (free_btree_node_chararray(node), 1);
	return (free_btree_node_chararray(node), 0);
}

int	main()
{
	int	nb_err=0;
	// =[ CONTENT == STRING ]===================================================
	nb_err+=test_char(NULL);          // content == NULL
	nb_err+=test_char("");            // content == empty string
	nb_err+=test_char("0a");          // content != empty string
	nb_err+=test_char(" 0a");         // content != empty string
	nb_err+=test_char("01234 abcde"); // content != empty string
	// =[ CONTENT == STRING ARRAY ]=============================================
	const char *t0[1] = {NULL};
	const char *t1[2] = {"", NULL};
	const char *t2[4] = {"", "", "", NULL};
	const char *t3[4] = {"coucou", "petite", "perruche", NULL};
	nb_err+=test_chararray(NULL);
	nb_err+=test_chararray(t0);
	nb_err+=test_chararray(t1);
	nb_err+=test_chararray(t2);
	nb_err+=test_chararray(t3);
	return (nb_err);
}
