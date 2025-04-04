#include "libft.h"  // struct t_list

int	print_btree_content_is_char(t_btree *btree_node)
{
	if (!btree_node)
		return (ft_printf("NULL"));
	return (ft_printf("{c->''%s'',l->%p, r->%p}", btree_node->content, btree_node->left, btree_node->right));
}

int	main()
{
	int	nb_err=0;
	// =[ CONTENT == STRING ]===================================================
	t_btree	*n0 = ft_btreetnew(NULL);
	print_btree_content_is_char(n0);
	free(n0);
	return (nb_err);
}
