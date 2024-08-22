/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:47:03 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/22 09:51:13 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <memory.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include "MLX42/MLX42.h"
# include "libft/libft.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		height;
	int		right_edge;
	int		bottom_edge;
}	t_point;

typedef struct s_view
{
	float	zoom;
	float	width_offset;
	float	height_offset;
	float	rotation;
}	t_view;

typedef struct s_map
{
	int		height;
	int		width;
	int		smallest_x;
	int		biggest_x;
	int		smallest_y;
	int		biggest_y;
	t_point	**points;
}	t_map;

typedef struct fdf
{
	mlx_t		*mlx;
	t_view		view;
	mlx_image_t	*img;
	t_map		map;
	int32_t		win_height;
	int32_t		win_width;
}	t_fdf;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	x;
	int	xi;
	int	y;
	int	yi;
	int	d;
}	t_line;

void	get_dimensions(int fd, t_map *map, t_fdf *fdf);
void	parse_map(int fd, t_map *map, t_fdf *fdf);
void	set_zoom_factor(t_fdf *fdf);

void	isometric_transformation(t_map *map);
void	rotate_around_x(float deg, t_point *point);
void	rotate_around_y(float deg, t_point *point);
void	rotate_around_z(float deg, t_point *point);
void	center_map(t_fdf *fdf);

void	draw_map(t_fdf *fdf, t_map *map);
void	swap_p0_and_p1(t_line *line);
void	init_line(t_line *line, t_point p0, t_point p1);

void	validate_file(char *file);
int		count_substrings(const char *s, char c);
void	update_max_min_x_y(t_point *point, t_map *map);

void	add_hooks(mlx_t *mlx, t_fdf *fdf);

void	free_points(int row_index, t_map *map);
void	terminate_mlx(t_fdf *fdf);
void	fdf_mlx_error(t_fdf *fdf, int free_bol);
void	error(t_fdf *fdf, char *str, int free_bol);
void	exit_program(t_fdf *fdf);

#endif