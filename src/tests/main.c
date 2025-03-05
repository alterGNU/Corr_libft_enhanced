/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:10:29 by lagrondi          #+#    #+#             */
/*   Updated: 2024/09/21 20:33:39 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_printab(char **tab)
{
	int	i;

	i = -1;
	ft_putchar_fd('[', 1);
	while (tab[++i])
	{
		if (i)
			ft_putstr_fd(", ", 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(tab[i], 1);
		ft_putchar_fd('"', 1);
	}
	ft_putstr_fd("]\n", 1);
}

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	read_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("%s", line);
	free(line);
}

int	main(int ac, char **av)
{
	int		i;
	char	**tab;
	int		fd;

	ft_printf("\nTEST 1: ft_printf+ft_split:\n");
	i = 1;
	while (i < ac)
	{
		tab = ft_split(av[i], ' ');
		ft_putstr_fd(" - \"", 1);
		ft_putstr_fd(av[i], 1);
		ft_printf("\" devient un tableau de taille %d : ", ft_tablen(tab));
		ft_printab(tab);
		ft_putchar_fd('\n', 1);
		ft_free_tab(tab);
		i++;
	}
	ft_printf("\nTEST 2: ft_get_next_line: (lis le fichier actuel):\n");
	fd = open("tests/main.c", O_RDONLY);
	if (fd < 0)
		return (1);
	read_file(fd);
	ft_putchar_fd('\n', 1);
	close(fd);
	return (0);
}
