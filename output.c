#include "bsq.h"

void	fill_square(t_map *map, t_square square)
{
	int	i;
	int	j;

	i = 0;
	while (i < square.size)
	{
		j = 0;
		while (j < square.size)
		{
			map->grid[square.y + i][square.x + j] = map->full;
			j++;
		}
		i++;
	}
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		ft_putstr(map->grid[i]);
		ft_putchar('\n');
		i++;
	}
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->rows)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

void	free_quadtree(t_quadtree *tree)
{
	if (!tree)
		return ;
	free_quadtree(tree->nw);
	free_quadtree(tree->ne);
	free_quadtree(tree->sw);
	free_quadtree(tree->se);
	free(tree);
}