/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_result.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:24:52 by lagrondi          #+#    #+#             */
/*   Updated: 2025/03/02 20:34:36 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

void	ft_print_test(const char *str, int (*fun)(void *))
{
	size_t	len;
	size_t	i;

	len = strlen(str);
	i = 0;
	while (i < len)
	{
		write(1, str++, 1);
		i++;
	}
	write(1, " ", 1);
	write(1, FAIL, 1);
	write(1, "\n", 1);
}
