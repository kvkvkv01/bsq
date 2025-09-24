/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caualves <caualves@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:32:49 by caualves          #+#    #+#             */
/*   Updated: 2025/09/24 11:33:22 by caualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
}			t_map;

typedef struct s_quadtree
{
	int					x;
	int					y;
	int					size;
	int					has_obstacle;
	struct s_quadtree	*nw;
	struct s_quadtree	*ne;
	struct s_quadtree	*sw;
	struct s_quadtree	*se;
}						t_quadtree;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
}		t_square;

t_map			*parse_map(int fd);
t_quadtree		*build_quadtree(t_map *map, int x, int y, int size);
t_square		find_largest_square(t_quadtree *tree, t_map *map);
void			fill_square(t_map *map, t_square square);
void			print_map(t_map *map);
void			free_map(t_map *map);
void			free_quadtree(t_quadtree *tree);
int				ft_strlen(char *str);
char			*ft_strdup(char *str);
void			ft_putstr(char *str);
void			ft_putchar(char c);

#endif