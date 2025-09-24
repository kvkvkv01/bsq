#include "bsq.h"

t_quadtree	*create_node(int x, int y, int size)
{
	t_quadtree	*node;

	node = malloc(sizeof(t_quadtree));
	if (!node)
		return (NULL);
	node->x = x;
	node->y = y;
	node->size = size;
	node->has_obstacle = 0;
	node->nw = NULL;
	node->ne = NULL;
	node->sw = NULL;
	node->se = NULL;
	return (node);
}

int	check_obstacle(t_map *map, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size && y + i < map->rows)
	{
		j = 0;
		while (j < size && x + j < map->cols)
		{
			if (map->grid[y + i][x + j] == map->obstacle)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_quadtree	*build_leaf(t_map *map, int x, int y, int size)
{
	t_quadtree	*node;

	node = create_node(x, y, size);
	if (!node)
		return (NULL);
	node->has_obstacle = check_obstacle(map, x, y, size);
	return (node);
}

t_quadtree	*build_internal(t_map *map, int x, int y, int size)
{
	t_quadtree	*node;
	int			half;

	node = create_node(x, y, size);
	if (!node)
		return (NULL);
	half = size / 2;
	node->nw = build_quadtree(map, x, y, half);
	node->ne = build_quadtree(map, x + half, y, half);
	node->sw = build_quadtree(map, x, y + half, half);
	node->se = build_quadtree(map, x + half, y + half, half);
	if (node->nw && node->nw->has_obstacle)
		node->has_obstacle = 1;
	if (node->ne && node->ne->has_obstacle)
		node->has_obstacle = 1;
	if (node->sw && node->sw->has_obstacle)
		node->has_obstacle = 1;
	if (node->se && node->se->has_obstacle)
		node->has_obstacle = 1;
	return (node);
}

t_quadtree	*build_quadtree(t_map *map, int x, int y, int size)
{
	if (size <= 4)
		return (build_leaf(map, x, y, size));
	return (build_internal(map, x, y, size));
}