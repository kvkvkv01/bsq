/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caualves <caualves@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:32:53 by caualves          #+#    #+#             */
/*   Updated: 2025/09/24 11:33:08 by caualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	get_max_dimension(int rows, int cols)
{
	int	max;
	int	power;

	max = rows;
	if (cols > max)
		max = cols;
	power = 1;
	while (power < max)
		power = power * 2;
	return (power);
}

void	process_map(int fd)
{
	t_map		*map;
	t_quadtree	*tree;
	t_square	square;
	int			tree_size;

	map = parse_map(fd);
	if (!map)
	{
		ft_putstr("map error\n");
		return ;
	}
	tree_size = get_max_dimension(map->rows, map->cols);
	tree = build_quadtree(map, 0, 0, tree_size);
	square = find_largest_square(tree, map);
	if (square.size > 0)
		fill_square(map, square);
	print_map(map);
	free_quadtree(tree);
	free_map(map);
}

void	process_files(int argc, char **argv)
{
	int	i;
	int	fd;

	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			ft_putstr("map error\n");
		else
		{
			process_map(fd);
			close(fd);
		}
		if (i < argc - 1)
			ft_putchar('\n');
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		process_map(0);
	else
		process_files(argc, argv);
	return (0);
}