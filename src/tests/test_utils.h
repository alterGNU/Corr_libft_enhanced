/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:39:43 by lagrondi          #+#    #+#             */
/*   Updated: 2025/03/02 20:32:09 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_H
// -[ DEFINE ]------------------------------------------------------------------
# define TEST_UTILS_H
# define TAB "      "
# define FAIL "❌"
# define PASS "❎"
// -[ INCLUDE ]-----------------------------------------------------------------
# include <unistd.h>
/*
 * write
 */
# include <stdio.h>
/*
 * printf
 */
# include <stdlib.h>
/*
 * free
 * malloc
 */
# include <string.h>
/* 
 * bzero
 * strcmp
 */
// -[ FUNCTIONS ]---------------------------------------------------------------
// memblock_utils.c
void	ft_print_memblock(void	*ptr, size_t size);
int		ft_compare_memblock(void *p1, void *p2, size_t size);
// int_array_utils.c
void	ft_print_int_array(int *tab, size_t size);
int		ft_compare_int_arrays(int *t1, int *t2, size_t size);
// ft_print_result.c
void	ft_print_test_fail(const char *str, int (*fun)(void *);
#endif
