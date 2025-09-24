#include "bsq.h"

int	is_valid_square(t_map *map, int x, int y, int size)
{
	int	i;
	int	j;

	if (x + size > map->cols || y + size > map->rows)
		return (0);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (map->grid[y + i][x + j] == map->obstacle)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	update_best(t_square *best, int x, int y, int size)
{
	if (size > best->size)
	{
		best->x = x;
		best->y = y;
		best->size = size;
	}
	else if (size == best->size)
	{
		if (y < best->y || (y == best->y && x < best->x))
		{
			best->x = x;
			best->y = y;
			best->size = size;
		}
	}
}

void	try_square(t_map *map, int x, int y, t_square *best)
{
	int	size;

	size = 1;
	while (is_valid_square(map, x, y, size))
	{
		update_best(best, x, y, size);
		size++;
	}
}

t_square	find_largest_square(t_quadtree *tree, t_map *map)
{
	t_square	best;
	int			x;
	int			y;

	(void)tree;
	best.x = 0;
	best.y = 0;
	best.size = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->grid[y][x] == map->empty)
				try_square(map, x, y, &best);
			x++;
		}
		y++;
	}
	return (best);
}