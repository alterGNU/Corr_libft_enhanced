/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:32:26 by lagrondi          #+#    #+#             */
/*   Updated: 2025/03/02 18:00:30 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

void	ft_print_int_array(int *tab, size_t size)
{
	size_t	i;

	printf("[");
	i = 0;
	while (i < size)
	{
		printf("%d", tab[i]);
		if (i + 1 < size)
			printf(", ");
		i++;
	}
	printf("]\n");
}

int	ft_compare_int_arrays(int *t1, int *t2, size_t size)
{
	int		nb_diff;
	size_t	i;

	nb_diff = 0;
	i = 0;
	while (i < size)
	{
		if (t1[i] != t2[i])
			nb_diff++;
		i++;
	}
	return (nb_diff);
}
