/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memblock_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:03:25 by lagrondi          #+#    #+#             */
/*   Updated: 2025/03/02 18:39:14 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

static char	conv_hex_to_ascci(char hex)
{
	if (hex < 10)
		return (hex + '0');
	return (hex + 'a' - 10);
}

/*
 * Print memory block
 */
void	ft_print_memblock(void	*ptr, size_t size)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	byte;
	char			hex1;
	char			hex2;

	str = (unsigned char *)ptr;
	i = 0;
	write(1, TAB, strlen(TAB));
	write(1, "[", 1);
	while (i < size)
	{
		byte = str[i];
		hex1 = (byte >> 4) & 0x0F;
		hex2 = byte & 0x0F;
		hex1 = conv_hex_to_ascci(hex1);
		hex2 = conv_hex_to_ascci(hex2);
		write(1, &hex1, 1);
		write(1, &hex2, 1);
		if (i + 1 < size)
			write(1, "|", 1);
		i++;
	}
	write(1, "]", 1);
}

/*
 * Compare 2 memory block address:
 * return 0 if all block have same value, else return nb of differences found
 */
int	ft_compare_memblock(void *p1, void *p2, size_t size)
{
	unsigned char	*byte1;
	unsigned char	*byte2;
	size_t			i;
	int				diff_count;

	byte1 = (unsigned char *)p1;
	byte2 = (unsigned char *)p2;
	diff_count = 0;
	i = 0;
	while (i < size)
	{
		if (byte1[i] != byte2[i])
			diff_count++;
		i++;
	}
	return (diff_count);
}
