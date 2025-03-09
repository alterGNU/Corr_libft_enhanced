/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:24:28 by lagrondi          #+#    #+#             */
/*   Updated: 2025/03/09 14:50:01 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_print_char_array(char **tab)
{
	int	i;

	ft_printf("[");
	i = -1;
	while (tab[++i])
	{
		ft_printf("\"%s\"", tab[i]);
		if (tab[i + 1])
			ft_printf(", ", tab[i]);
	}
	ft_printf("]");
}

void	ft_print_int_array(int *tab, int size)
{
	int	i;

	ft_printf("[");
	i = -1;
	while (++i < size)
	{
		ft_printf("%d", tab[i]);
		if (i + 1 < size)
			ft_printf(", ", tab[i]);
	}
	ft_printf("]");
}

void	ft_close_fds(int *tab, int size)
{
	int	i;

	i = -1;
	ft_printf("Launch ft_close_fds()");
	while (++i < size)
	{
		if (tab[i] >= 0)
		{
			ft_printf("--->close(tab[i]=%d)", i, tab[i]);
			close(tab[i]);
		}
		else
			ft_printf("--->CANT close(tab[i]=%d)", i, tab[i]);
	}
	ft_printf("\n");
}

int	main(int ac, char **av)
{
	int		i;
	int		*fds;
	char	*line;
	int		one_file_open;

	av++;
	ac--;
	ft_printf("ac=[%d]\nav=", ac);
	ft_print_char_array(av);
	ft_printf("\n");
	ft_printf("create int fds[%d + 1]=[..., 0] (null terminated)\n", ac);
	fds = (int *)ft_calloc(ac + 1, sizeof(int));
	if (!fds)
		return (ft_putstr_fd("Error:ft_calloc()\n", 2), 1);
	ft_printf("fds=");
	ft_print_int_array(fds, ac);
	ft_printf("\n");
	i = 0;
	one_file_open = 0;
	while (*av)
	{
		ft_printf("fds[%d]=open(\"\%s\", O_RDONLY)\n", i, *av);
		fds[i] = open(*av, O_RDONLY);
		if (fds[i] < 0)
		{
			ft_printf("ERROR:can not open \"%s\"\n", *av);
			return (ft_close_fds(fds, i), free(fds), \
					ft_putstr_fd("Error:open()\n", 2), 1);
		}
		ft_printf("open \"%s\" successfully\n", *av);
		av++;
		one_file_open++;
		i++;
	}
	ft_printf("fds =");
	ft_print_int_array(fds, ac);
	ft_printf("\n");
	while (one_file_open)
	{
		i = 0;
		while (i < ac)
		{
			i++;
		}
	}
	return (ft_close_fds(fds, ac), free(fds), ft_printf("...THE END.\n"), 0);
}
