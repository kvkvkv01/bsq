#include "bsq.h"

char	*read_first_line(int fd)
{
	char	buffer[1024];
	int		i;
	int		bytes_read;

	i = 0;
	while (i < 1023)
	{
		bytes_read = read(fd, &buffer[i], 1);
		if (bytes_read <= 0 || buffer[i] == '\n')
			break ;
		i++;
	}
	buffer[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(buffer));
}

int	parse_first_line(char *line, t_map *map)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	if (len < 4)
		return (0);
	map->full = line[len - 1];
	map->obstacle = line[len - 2];
	map->empty = line[len - 3];
	if (map->empty == map->obstacle || map->empty == map->full
		|| map->obstacle == map->full)
		return (0);
	line[len - 3] = '\0';
	map->rows = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] < '0' || line[i] > '9')
			return (0);
		map->rows = map->rows * 10 + (line[i] - '0');
		i++;
	}
	return (map->rows > 0);
}

char	*read_line(int fd)
{
	char	buffer[4096];
	int		i;
	int		bytes_read;

	i = 0;
	while (i < 4095)
	{
		bytes_read = read(fd, &buffer[i], 1);
		if (bytes_read <= 0 || buffer[i] == '\n')
			break ;
		i++;
	}
	buffer[i] = '\0';
	if (i == 0 && bytes_read <= 0)
		return (NULL);
	return (ft_strdup(buffer));
}

int	validate_line(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != map->empty && line[i] != map->obstacle)
			return (0);
		i++;
	}
	if (map->cols == 0)
		map->cols = i;
	else if (map->cols != i)
		return (0);
	return (1);
}

t_map	*parse_map(int fd)
{
	t_map	*map;
	char	*first_line;
	int		i;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	first_line = read_first_line(fd);
	if (!first_line || !parse_first_line(first_line, map))
	{
		free(first_line);
		free(map);
		return (NULL);
	}
	free(first_line);
	map->grid = malloc(sizeof(char *) * (map->rows + 1));
	if (!map->grid)
	{
		free(map);
		return (NULL);
	}
	map->cols = 0;
	i = 0;
	while (i < map->rows)
	{
		map->grid[i] = read_line(fd);
		if (!map->grid[i] || !validate_line(map->grid[i], map))
		{
			while (i >= 0)
			{
				free(map->grid[i]);
				i--;
			}
			free(map->grid);
			free(map);
			return (NULL);
		}
		i++;
	}
	map->grid[i] = NULL;
	if (map->cols == 0)
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}