/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:03:52 by lagrondi          #+#    #+#             */
/*   Updated: 2025/03/02 20:29:18 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"
#include "libft.h"

int	test_void(void)
{
	void	*real;
	void	*ft;
	int		i;
	int		nb_error;
	int		test;

	nb_error = 0;
	real = malloc(16);
	ft = malloc(16);
	i = 0;
	while (i < 16)
	{
		memset(real, '1', 16);
		memset(ft, '1', 16);
		bzero(real, i);
		ft_bzero(ft, i);
		test = ft_compare_memblock(real, ft, 16);
		if (test)
		{
			ft_print_test_fail("memblock differ:");
			ft_print_memblock(real, 16);
			ft_print_memblock(ft, 16);
		}
		nb_error += test;
		i++;
	}
	return (nb_error);
}

int	main(void)
{
	int	nb_err;

	nb_err = 0;
	nb_err += test_void();
	return (write(1, "\n", 1), nb_err);
    //printf("\nTEST SUR CHAINES DE CARACTERES:\n");
    //char sa0[16];
    //char sb0[16];
    //strcpy(sa0, "");
    //strcpy(sb0, "");
    //nb_err+=compare_str(sa0, sb0, 0);

    //char sa1[16];
    //char sb1[16];
    //strcpy(sa1, "Coucou.");
    //strcpy(sb1, "Coucou.");
    //nb_err+=compare_str(sa1, sb1, 0);
    //strcpy(sa1, "Coucou.");
    //strcpy(sb1, "Coucou.");
    //nb_err+=compare_str(sa1, sb1, 4);
    //strcpy(sa1, "Coucou.");
    //strcpy(sb1, "Coucou.");
    //nb_err+=compare_str(sa1, sb1, 7);

// -//[ 	COMPARE TABLEAUX ENTIERS ]-----------------------------------------------
    //printf("\nTEST SUR TABLEAUX d'ENTIERS:\n");
	//int	t0[0] = {};
	//int	T0[0] = {};
	//nb_err+=compare_tab(t0, T0, 0, 0);

	//int	t1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	//int	T1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	//for (int i=0;i<=9;i++)
	//	nb_err+=compare_tab(t1, T1, 9, i);
	//return (nb_err);
}
